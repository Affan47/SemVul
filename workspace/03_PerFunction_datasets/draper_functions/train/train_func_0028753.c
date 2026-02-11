gettmpfilenameargs(const char **time_buf,
	const char **pid_buf, const char **hostname_buf)
{
	if (!hostnameptr)
	{
	time_t	t;
	pid_t	p;

		time(&t);
		timeptr=tbuf+sizeof(tbuf)-1;
		*timeptr=0;
		do
		{
			*--timeptr= '0' + (t % 10);
			t /= 10;
		} while (t);

		p=getpid();
		pidptr=pbuf+sizeof(pbuf)-1;
		*pidptr=0;
		do
		{
			*--pidptr= '0' + (p % 10);
			p /= 10;
		} while (p);
		hostnameptr=config_me();
	}
	*time_buf=timeptr;
	*pid_buf=pidptr;
	*hostname_buf=hostnameptr;
}
