async_wait_for_write(gc)
struct cache *gc;
{
	struct cache_ent *ce;
	size_t ret,retval;
	if(gc->w_head==0)
		return;
	ce=gc->w_head;
	gc->w_head=ce->forward;
	gc->w_count--;
	ce->forward=0;
	if(ce==gc->w_tail)
		gc->w_tail=0;


#ifdef _LARGEFILE64_SOURCE
#ifdef __LP64__
	while((ret=aio_error(&ce->myaiocb))== EINPROGRESS)
	{
		async_suspend(ce);
	}
#else
	while((ret=aio_error64(&ce->myaiocb64))== EINPROGRESS)
	{
		async_suspend(ce);
	}
#endif
#else
	while((ret=aio_error(&ce->myaiocb))== EINPROGRESS)
	{
		async_suspend(ce);
	}
#endif
	if(ret)
	{
		printf("aio_error 5: ret %d %d\n",ret,errno);
#ifdef _LARGEFILE64_SOURCE
#ifdef __LP64__
		printf("fd %d offset %lld size %d\n",
			ce->myaiocb.aio_fildes,
			ce->myaiocb.aio_offset,
			ce->myaiocb.aio_nbytes);
#else
		printf("fd %d offset %lld size %d\n",
			ce->myaiocb64.aio_fildes,
			ce->myaiocb64.aio_offset,
			ce->myaiocb64.aio_nbytes);
#endif
#else
		printf("fd %d offset %lld size %d\n",
			ce->myaiocb.aio_fildes,
			ce->myaiocb.aio_offset,
			ce->myaiocb.aio_nbytes);
#endif
		exit(181);
	}

#ifdef _LARGEFILE64_SOURCE
#ifdef __LP64__
	retval=aio_return(&ce->myaiocb);
#else
#if defined(__CrayX1__)
	retval=aio_return64((aiocb64_t *)&ce->myaiocb64);
#else
	retval=aio_return64((struct aiocb64 *)&ce->myaiocb64);
#endif

#endif
#else
	retval=aio_return(&ce->myaiocb);
#endif
	if((int)retval < 0)
	{
		printf("aio_return error: %d\n",errno);
	}

	if(!ce->direct)
	{

		free((void *)(ce->real_address));
		free((void *)ce);
	}

}
