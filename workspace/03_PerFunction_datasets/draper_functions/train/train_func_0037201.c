copyfile(int out_fd, int in_fd, off_t *offset, size_t count)
	{
	size_t done=0;
	ssize_t ret;
	while( done<count )
		{
		if( (ret=sendfile(out_fd, in_fd, offset, count-done)) < 0 )
			{
			if( errno == EINVAL && done==0 )
				return slow_copyfile(out_fd, in_fd, offset, count);
			perror("sendfile");
			exit(EXIT_FAILURE);
			}
		else if( ret == 0 )
			{
			fprintf(stderr,"unexpected end of file\n");
			exit(EXIT_FAILURE);
			}
		else done+=ret;
		}
	return done;
	}
