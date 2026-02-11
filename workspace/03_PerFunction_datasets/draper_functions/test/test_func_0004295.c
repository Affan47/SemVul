async_write(gc,fd,buffer,size,offset,depth)
struct cache *gc;
long long fd,size;
char *buffer;
off64_t offset;
long long depth;
{
	struct cache_ent *ce;
	size_t ret;
	ce=allocate_write_buffer(gc,fd,offset,size,(long long)LIO_WRITE,depth,0LL,(char *)0,(char *)0);
	ce->direct=0;
#ifdef _LARGEFILE64_SOURCE
#ifdef __LP64__
	mbcopy(buffer,(char *)(ce->myaiocb.aio_buf),(size_t)size);
#else
	mbcopy(buffer,(char *)(ce->myaiocb64.aio_buf),(size_t)size);
#endif
#else
	mbcopy(buffer,(char *)(ce->myaiocb.aio_buf),(size_t)size);
#endif
	async_put_on_write_queue(gc,ce);


again:
#ifdef _LARGEFILE64_SOURCE
#ifdef __LP64__
	ret=aio_write(&ce->myaiocb);
#else
	ret=aio_write64(&ce->myaiocb64);
#endif
#else
	ret=aio_write(&ce->myaiocb);
#endif
	if(ret==-1)
	{
		if(errno==EAGAIN)
		{
			async_wait_for_write(gc);
			goto again;
		}
		if(errno==0)
		{

			async_wait_for_write(gc);
			goto again;
		}
		else
		{
			printf("Error in aio_write: ret %d errno %d count %lld\n",ret,errno,gc->w_count);


			exit(177);
		}
	}
	return((ssize_t)size);
}
