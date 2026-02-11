poll( struct pollfd *ufds, unsigned int nfds, int timeout )
{
	unsigned i;
	int result=0,maxfd=0;
	struct timeval tv;
	fd_set rfds, wfds, efds;

	FD_ZERO(&rfds);
	FD_ZERO(&wfds);
	FD_ZERO(&efds);

	for(i=0;i<nfds;i++) {
		int fd = ufds[i].fd;
		if(fd<0 || fd>=pointer_count || pointers[fd]==0) {
			continue;

		} else {
			if(ufds[i].events&POLLIN)  FD_SET(fd,&rfds);
			if(ufds[i].events&POLLOUT) FD_SET(fd,&wfds);
			if(ufds[i].events&POLLERR) FD_SET(fd,&efds);
		}
		maxfd = MAX(maxfd,fd+1);
	}

	if(timeout>=0) {
		tv.tv_sec = timeout / 1000;
		tv.tv_usec = 1000*(timeout % 1000);
		result = this->select(maxfd,&rfds,&wfds,&efds,&tv);
	} else {
		result = this->select(maxfd,&rfds,&wfds,&efds,0);
	}

	if(result>0) {
		for(i=0;i<nfds;i++) {
			int fd = ufds[i].fd;
			ufds[i].revents = 0;
			if(fd<0 || fd>=pointer_count || pointers[fd]==0) {
				ufds[i].revents |= POLLNVAL;
				continue;
			}
			if(ufds[i].events&POLLIN&&FD_ISSET(fd,&rfds))
				ufds[i].revents |= POLLIN;
			if(ufds[i].events&POLLOUT&&FD_ISSET(fd,&wfds))
				ufds[i].revents |= POLLOUT;
			if(ufds[i].events&POLLERR&&FD_ISSET(fd,&efds))
				ufds[i].revents |= POLLERR;
		}
	}

	return result;
}
