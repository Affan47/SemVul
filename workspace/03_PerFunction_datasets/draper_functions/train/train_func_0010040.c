BIO_new_fd(int fd,int close_flag)
	{
	BIO *ret;
	ret=BIO_new(BIO_s_fd());
	if (ret == NULL) return(NULL);
	BIO_set_fd(ret,fd,close_flag);
	return(ret);
	}
