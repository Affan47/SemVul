f_usertime(void)
{
#if defined(HAVE_GETRUSAGE)
	struct rusage usage;
	int who = RUSAGE_SELF;
	int status;
	NUMBER *ret;
	NUMBER *secret;
	NUMBER *usecret;


	status = getrusage(who, &usage);
	if (status < 0) {

	    return qlink(&_qzero_);
	}


	secret = stoq(usage.ru_utime.tv_sec);
	usecret = iitoq((long)usage.ru_utime.tv_usec, 1000000L);
	ret = qqadd(secret, usecret);
	qfree(secret);
	qfree(usecret);


	return ret;

#else

	return qlink(&_qzero_);
#endif
}
