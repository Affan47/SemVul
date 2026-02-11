print_net_icmp_stats(struct activity *a, int prev, int curr,
				     unsigned long long itv)
{
	struct stats_net_icmp
		*snic = (struct stats_net_icmp *) a->buf[curr],
		*snip = (struct stats_net_icmp *) a->buf[prev];

	if (dis) {
		printf("\n%-11s    imsg/s    omsg/s    iech/s   iechr/s    oech/s"
		       "   oechr/s     itm/s    itmr/s     otm/s    otmr/s"
		       "  iadrmk/s iadrmkr/s  oadrmk/s oadrmkr/s\n", timestamp[!curr]);
	}

	printf("%-11s %9.2f %9.2f %9.2f %9.2f %9.2f %9.2f %9.2f %9.2f %9.2f %9.2f"
	       " %9.2f %9.2f %9.2f %9.2f\n", timestamp[curr],
	       S_VALUE(snip->InMsgs,           snic->InMsgs,           itv),
	       S_VALUE(snip->OutMsgs,          snic->OutMsgs,          itv),
	       S_VALUE(snip->InEchos,          snic->InEchos,          itv),
	       S_VALUE(snip->InEchoReps,       snic->InEchoReps,       itv),
	       S_VALUE(snip->OutEchos,         snic->OutEchos,         itv),
	       S_VALUE(snip->OutEchoReps,      snic->OutEchoReps,      itv),
	       S_VALUE(snip->InTimestamps,     snic->InTimestamps,     itv),
	       S_VALUE(snip->InTimestampReps,  snic->InTimestampReps,  itv),
	       S_VALUE(snip->OutTimestamps,    snic->OutTimestamps,    itv),
	       S_VALUE(snip->OutTimestampReps, snic->OutTimestampReps, itv),
	       S_VALUE(snip->InAddrMasks,      snic->InAddrMasks,      itv),
	       S_VALUE(snip->InAddrMaskReps,   snic->InAddrMaskReps,   itv),
	       S_VALUE(snip->OutAddrMasks,     snic->OutAddrMasks,     itv),
	       S_VALUE(snip->OutAddrMaskReps,  snic->OutAddrMaskReps,  itv));
}
