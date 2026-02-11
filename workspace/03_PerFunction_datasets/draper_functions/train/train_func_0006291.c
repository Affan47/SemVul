GetTraffic()
{
	int i;
	struct timeval tp;
	ulonglong t1,t2;
	ulonglong n = 0;

	gettimeofday(&tp,NULL);

	t1 = ((tp.tv_sec*1000)+(tp.tv_usec/1000));

	i = m_AverageTransferRate.index;

	if ( i == 9 )
		i = 0;
	else
	{
		i++;
	}

	t2 = ((m_AverageTransferRate.tv[i].tv_sec*1000)+(m_AverageTransferRate.tv[i].tv_usec/1000));

	if ( (t2 == 0) && (i > 0) )
	{
		i = 0;
	}

	t2 = ((m_AverageTransferRate.tv[i].tv_sec*1000)+(m_AverageTransferRate.tv[i].tv_usec/1000));

	if ( t2 != 0 )
	{
		t1 = t1-t2;

		if ( t1 > 0 )
		{
		for(i=0,t2=0;i<10;i++)
		{
			n += m_AverageTransferRate.transfered[i];
		}

		n = (n*1000)/t1;
		}
	}
	else
	{
		DPRINTF("time is null\n");
	}

	return n;
}
