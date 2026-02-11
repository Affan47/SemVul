job_pack(struct spq *to, struct spq *from)
{
	to->spq_job = htonl((ULONG) from->spq_job);
	to->spq_netid = 0L;
	to->spq_orighost = from->spq_orighost == 0? myhostid: from->spq_orighost;
	to->spq_rslot = htonl((ULONG) from->spq_rslot);
	to->spq_time = htonl((ULONG) from->spq_time);
	to->spq_proptime = 0L;
	to->spq_starttime = htonl((ULONG) from->spq_starttime);
	to->spq_hold = htonl((ULONG) from->spq_hold);
	to->spq_nptimeout = htons(from->spq_nptimeout);
	to->spq_ptimeout = htons(from->spq_ptimeout);
	to->spq_size = htonl((ULONG) from->spq_size);
	to->spq_posn = htonl((ULONG) from->spq_posn);
	to->spq_pagec = htonl((ULONG) from->spq_pagec);
	to->spq_npages = htonl((ULONG) from->spq_npages);

	to->spq_cps = from->spq_cps;
	to->spq_pri = from->spq_pri;
	to->spq_wpri = htons((USHORT) from->spq_wpri);

	to->spq_jflags = htons(from->spq_jflags);
	to->spq_sflags = from->spq_sflags;
	to->spq_dflags = from->spq_dflags;

	to->spq_extrn = htons(from->spq_extrn);
	to->spq_pglim = 0;

	to->spq_class = htonl(from->spq_class);

	to->spq_pslot = htonl(-1L);

	to->spq_start = htonl((ULONG) from->spq_start);
	to->spq_end = htonl((ULONG) from->spq_end);
	to->spq_haltat = htonl((ULONG) from->spq_haltat);
	to->spq_uid = htonl(from->spq_uid);

	strncpy(to->spq_uname, from->spq_uname, UIDSIZE+1);
	strncpy(to->spq_puname, from->spq_puname, UIDSIZE+1);
	strncpy(to->spq_file, from->spq_file, MAXTITLE+1);
	strncpy(to->spq_form, from->spq_form, MAXFORM+1);
	strncpy(to->spq_ptr, from->spq_ptr, JPTRNAMESIZE+1);
	strncpy(to->spq_flags, from->spq_flags, MAXFLAGS+1);
}
