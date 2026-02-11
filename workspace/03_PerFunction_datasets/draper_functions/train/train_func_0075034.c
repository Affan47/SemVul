my_unap( unsigned long long microsecs )
#else
void
my_unap( microsecs )
unsigned long long microsecs;
#endif
{
	double timein, timeout;
	unsigned long usecs;

	usecs = (unsigned long) microsecs;
	usecs = (usecs/1000)*1000;

	timein=time_so_far1();
	usleep(usecs);

	while(1)
	{
		timeout=time_so_far1();
		if(timeout-timein > microsecs)
		   break;
	}
}
