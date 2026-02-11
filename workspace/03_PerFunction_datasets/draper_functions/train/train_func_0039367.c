RAND_cleanup(void)
	{
	const RAND_METHOD *meth = RAND_get_rand_method();
	if (meth && meth->cleanup)
		meth->cleanup();
	RAND_set_rand_method(NULL);
	}
