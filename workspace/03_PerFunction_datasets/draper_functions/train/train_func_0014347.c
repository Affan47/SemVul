nrcv_(int *nevent, int *ntype, int *nlength, int *nflags, int *ndata,
      int *ndsize, char *nmsg, int *ierror)
{
	struct nmsg	nhead;

	nhead.nh_event = *nevent;
	nhead.nh_type = *ntype;
	nhead.nh_length = *nlength;
	nhead.nh_flags = *nflags;
	nhead.nh_msg = nmsg;

	if (nrecv(&nhead)) {
		*ierror = errno;
	} else {
		*ierror = 0;
		memcpy((char *) ndata, (char *) nhead.nh_data,
			(*ndsize > sizeof(nhead.nh_data))
                        ? sizeof(nhead.nh_data) : *ndsize);
                *ntype = nhead.nh_type;
                *nlength = nhead.nh_length;
	}
}
