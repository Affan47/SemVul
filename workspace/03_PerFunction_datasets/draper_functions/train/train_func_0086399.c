thread_mix_test(void *x)
#else
void *
thread_mix_test(x)
#endif
{
	int selector;
	int num_readers;
	long xx;

	mix_test = 1;
#ifdef NO_THREADS
	xx=chid;
#else
	if(use_thread)
	{
		xx = (long)x;
	}
	else
	{
		xx=(long)chid;
	}
#endif
	if(pct_read!=0)
	{
 		num_readers = (pct_read * num_child)/100;
                if(xx < num_readers)
                        selector=0;
                else
                        selector=1;
	}
	else
	{
	   if(Kplus_flag)
	   {
		if(xx+1 <= Kplus_readers)
			selector=0;
		else
			selector=1;
	   }
	   else
	   {

		selector= ((int)xx) % 2;
	   }
	}
	if(selector==0)
	{
		if(seq_mix)
			thread_read_test(x);
		else
			thread_ranread_test(x);
	}
	else
	{
		if(seq_mix)
			thread_write_test(x);
		else
			thread_ranwrite_test(x);
	}
	return(0);
}
