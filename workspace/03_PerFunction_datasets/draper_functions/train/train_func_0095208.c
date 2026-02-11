igrp_entry_print(register struct igrprte *igr, register int is_interior,
    register int is_exterior)
{
	register u_int delay, bandwidth;
	u_int metric, mtu;

	if (is_interior)
		printf(" *.%d.%d.%d", igr->igr_net[0],
		    igr->igr_net[1], igr->igr_net[2]);
	else if (is_exterior)
		printf(" X%d.%d.%d.0", igr->igr_net[0],
		    igr->igr_net[1], igr->igr_net[2]);
	else
		printf(" %d.%d.%d.0", igr->igr_net[0],
		    igr->igr_net[1], igr->igr_net[2]);

	delay = EXTRACT_24BITS(igr->igr_dly);
	bandwidth = EXTRACT_24BITS(igr->igr_bw);
	metric = bandwidth + delay;
	if (metric > 0xffffff)
		metric = 0xffffff;
	mtu = EXTRACT_16BITS(igr->igr_mtu);

	printf(" d=%d b=%d r=%d l=%d M=%d mtu=%d in %d hops",
	    10 * delay, bandwidth == 0 ? 0 : 10000000 / bandwidth,
	    igr->igr_rel, igr->igr_ld, metric,
	    mtu, igr->igr_hct);
}
