pull_velocity (Scsi_Command &cmd,unsigned char *d)
{ unsigned int len;
  int v,err;
  class autofree perf;

#if 0
    if ((d[4]&2) == 0)	return -1;
#endif

    len = (d[0]<<24|d[1]<<16|d[2]<<8|d[3])-4;
    if (len%16)		return -1;
    if (len==0)		return -1;

    len += 8;
    if (len == (8+16))
    {	velocity = d[8+ 4]<<24|d[8+ 5]<<16|d[8+ 6]<<8|d[8+ 7];
	v =        d[8+12]<<24|d[8+13]<<16|d[8+14]<<8|d[8+15];
	if (v>velocity) velocity=v;
    }
    else
    { unsigned int n = (len-8)/16;
      unsigned char *p;

	perf = (unsigned char *)malloc (len);
	if (perf == NULL)
	    fprintf (stderr,":-( memory exhausted\n"),
	    exit(FATAL_START(ENOMEM));

	cmd[0]=0xAC;
	cmd[1]=4;
	cmd[8]=n>>8;
	cmd[9]=n;
	cmd[10]=0;
	cmd[11]=0;
	if ((err=cmd.transport(READ,perf,len)))
	    sperror ("GET CURRENT PERFORMANCE",err),
	    exit (FATAL_START(errno));


	for (p=perf+8,len-=8;len;p+=16,len-=16)
	{   v=p[ 4]<<24|p[ 5]<<16|p[ 6]<<8|p[ 7];
	    if (v > velocity) velocity = v;
	    v=p[12]<<24|p[13]<<16|p[14]<<8|p[15];
	    if (v > velocity) velocity = v;
	}
    }

  return 0;
}
