decode_read( struct pfs_process *p, int entering, int syscall, INT64_T *args )
{
	int fd = args[0];
	void *uaddr = POINTER(args[1]);
	pfs_size_t length = args[2];
	pfs_off_t offset = args[3];
	char *local_addr;

	if(entering) {
		if(!pfs_channel_alloc(0,length,&p->io_channel_offset)) {
			divert_to_dummy(p,-ENOMEM);
			return;
		}
		local_addr = pfs_channel_base() + p->io_channel_offset;

		if(syscall==SYSCALL32_read) {
			p->syscall_result = pfs_read(fd,local_addr,length);
		} else if(syscall==SYSCALL32_pread) {
			p->syscall_result = pfs_pread(fd,local_addr,length,offset);
		} else if(syscall==SYS_RECV) {
			p->syscall_result = pfs_recv(fd,local_addr,length,args[3]);
		} else if(syscall==SYS_RECVFROM) {
			p->syscall_result = pfs_recvfrom(fd,local_addr,length,args[3],(struct sockaddr*)POINTER(args[4]),(int*)POINTER(args[5]));
		}

		p->diverted_length = 0;

		if(p->syscall_result==0) {
			divert_to_dummy(p,0);
		} else if(p->syscall_result>0) {
			divert_to_channel(p,SYSCALL32_pread,uaddr,p->syscall_result,p->io_channel_offset);
			pfs_read_count += p->syscall_result;
		} else if( errno==EAGAIN ) {
			if(p->interrupted) {
				p->interrupted = 0;
				divert_to_dummy(p,-EINTR);
			} else if(pfs_is_nonblocking(fd)) {
				divert_to_dummy(p,-EAGAIN);
			} else {
				pfs_channel_free(p->io_channel_offset);
				p->state = PFS_PROCESS_STATE_WAITREAD;
				int rfd = pfs_get_real_fd(fd);
				if(rfd>=0) pfs_poll_wakeon(rfd,PFS_POLL_READ);
			}
		} else {
			divert_to_dummy(p,-errno);
		}
	} else {


		if( (p->syscall_result==-EINTR) && (p->diverted_length>0) ) {
			tracer_copy_out(p->tracer,pfs_channel_base()+p->io_channel_offset,uaddr,p->diverted_length);
			p->syscall_result = p->diverted_length;
			tracer_result_set(p->tracer,p->syscall_result);
		}

		pfs_channel_free(p->io_channel_offset);
	}
}
