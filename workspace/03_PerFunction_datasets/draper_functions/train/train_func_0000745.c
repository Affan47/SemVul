get_traj(FILE *traj_fd, long long *traj_size, float *delay, long which)
#else
long long
get_traj(traj_fd, traj_size, delay, which)
FILE *traj_fd;
long long *traj_size;
float *delay;
long which;
#endif
{
	long long traj_offset = 0;
	long long tmp2 = 0;
	int tmp = 0;
	int tokens;
	int ret=0;
	char *ret1,*where;
	char buf[200];
	char sbuf[200];
	int got_line;

	got_line=0;

	while(got_line==0)
	{
		tokens=0;
		ret1=fgets(buf,200,traj_fd);
		if(ret1==(char *)0)
		{
			printf("\n\n\tEarly end of telemetry file. Results not accurate.\n");
			signal_handler();
		}
		where=(char *)&buf[0];
		strcpy(sbuf,buf);
		if((*where=='#') || (*where=='\n'))
			continue;
		tokens++;
		strtok(where," ");
		while( (char *)(strtok( (char *)0," ")) != (char *)0)
		{
			tokens++;
		}
		got_line=1;
	}
	if(tokens == 3)
	{
#ifdef NO_PRINT_LLD
		ret=sscanf(sbuf,"%ld %ld %d\n",&traj_offset,&tmp2,&tmp);
#else
		ret=sscanf(sbuf,"%lld %lld %d\n",&traj_offset,&tmp2,&tmp);
#endif

		*traj_size=tmp2;
		*delay= ((float)tmp/1000);
	}
	if(tokens == 2)
	{
#ifdef NO_PRINT_LLD
		ret=sscanf(sbuf,"%ld %ld\n",&traj_offset,traj_size);
#else
		ret=sscanf(sbuf,"%lld %lld\n",&traj_offset,traj_size);
#endif
		*delay=compute_time;

	}
	if((tokens != 2) && (tokens !=3))
	{
		printf("\n\tInvalid entry in telemetry file. > %s <\n",sbuf);
		exit(178);
	}
	if(ret==EOF)
	{
		printf("\n\n\tEarly end of telemetry file. Results not accurate.\n");
		signal_handler();
	}
#ifdef DEBUG
#ifdef NO_PRINT_LLD
	if(!silent) printf("\nOffset %lld  Size %ld Compute delay %f\n",traj_offset, *traj_size,*delay);
#else
	if(!silent) printf("\nOffset %lld  Size %lld Compute delay %f\n",traj_offset, *traj_size,*delay);
#endif
#endif
	return(traj_offset);
}
