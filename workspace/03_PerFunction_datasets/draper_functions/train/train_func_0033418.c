sync_slave(struct _gps *master, struct _gps *slave, float8 *skew, int iter)
{
	float8		local;
	char	        *imsg;
	char	        *omsg;
	struct nmsg	inmsg;
	struct nmsg	outmsg;
	int		i;


	outmsg.nh_flags = DFLT8DATA;
	outmsg.nh_length = 0;
	sync_fill(slave, master, &outmsg);
	omsg = (char *) (&outmsg.nh_data[0]);


	inmsg.nh_flags = DFLT8DATA;
	inmsg.nh_length = 0;
	sync_fill(master, slave, &inmsg);
	imsg = (char *) (&inmsg.nh_data[0]);


	if (nrecv(&inmsg)) return(LAMERROR);
	if (nsend(&outmsg)) return(LAMERROR);


	for (i = 0; i < iter; i++) {

		if (nrecv(&inmsg)) return(LAMERROR);

		local = (float8) ttime();
		memcpy(omsg, (char *) &local, sizeof(float8));

		if (nsend(&outmsg)) return(LAMERROR);

	}

	if (nrecv(&inmsg)) return(LAMERROR);

	memcpy((char *) skew, imsg, sizeof(float8));

	return(0);
}
