nrecv(nhead)

struct nmsg		*nhead;

{
	struct nmsg	incoming;
	int4		remlen;
	char		*save_msg;


	if ((nhead->nh_flags & KTRY) && !(nhead->nh_flags & NOBUF)) {
		incoming.nh_event = nhead->nh_event;
		incoming.nh_type = nhead->nh_type;
		incoming.nh_flags = nhead->nh_flags;

		switch (nprobe(&incoming)) {

			case LAMERROR:
			return(LAMERROR);

			case 1:
			break;

			default:
			errno = EWOULDBLOCK;
			return(LAMERROR);
		}
	}


	remlen = nhead->nh_length;

	incoming.nh_event = nhead->nh_event;
	incoming.nh_type = nhead->nh_type;
	incoming.nh_flags = nhead->nh_flags | NMORE;
	incoming.nh_length = MAXNMSGLEN;
	incoming.nh_msg = nhead->nh_msg;

	while ((remlen > MAXNMSGLEN) && (incoming.nh_flags & NMORE)) {
		save_msg = incoming.nh_msg;

		if (nhead->nh_flags & NOBUF) {
			if (frecv(&incoming)) return(LAMERROR);
		} else {
			if (bfrecv(&incoming)) return(LAMERROR);
		}

		incoming.nh_msg = save_msg;
		remlen -= incoming.nh_length;
		incoming.nh_msg += incoming.nh_length;
	}

	if (incoming.nh_flags & NMORE) {


		incoming.nh_length = remlen;

		if (nhead->nh_flags & NOBUF) {
			if (frecv(&incoming)) return(LAMERROR);
		} else {
			if (bfrecv(&incoming)) return(LAMERROR);
		}

		remlen -= LAM_min(remlen, incoming.nh_length);


		while (incoming.nh_flags & NMORE) {
			incoming.nh_length = 0;

			if (nhead->nh_flags & NOBUF) {
				if (frecv(&incoming)) return(LAMERROR);
			} else {
				if (bfrecv(&incoming)) return(LAMERROR);
			}
		}
	}


	nhead->nh_length = nhead->nh_length - remlen;
	nhead->nh_type = incoming.nh_type;
	memcpy((char *) nhead->nh_data, (char *) incoming.nh_data,
			NHDSIZE * sizeof(int4));

	return(0);
}
