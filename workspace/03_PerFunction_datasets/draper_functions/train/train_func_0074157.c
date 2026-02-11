GetStatistics( RakNetStatistics *rns )
{
	unsigned i;
	RakNet::TimeUS time = RakNet::GetTimeUS();
	uint64_t uint64Denominator;
	double doubleDenominator;

	for (i=0; i < RNS_PER_SECOND_METRICS_COUNT; i++)
	{
		statistics.valueOverLastSecond[i]=bpsMetrics[i].GetBPS1Threadsafe(time);
		statistics.runningTotal[i]=bpsMetrics[i].GetTotal1();
	}

	memcpy(rns, &statistics, sizeof(statistics));

	if (rns->valueOverLastSecond[USER_MESSAGE_BYTES_SENT]+rns->valueOverLastSecond[USER_MESSAGE_BYTES_RESENT]>0)
		rns->packetlossLastSecond=(float)((double) rns->valueOverLastSecond[USER_MESSAGE_BYTES_RESENT]/((double) rns->valueOverLastSecond[USER_MESSAGE_BYTES_SENT]+(double) rns->valueOverLastSecond[USER_MESSAGE_BYTES_RESENT]));
	else
		rns->packetlossLastSecond=0.0f;

	rns->packetlossTotal=0.0f;
	uint64Denominator=(rns->runningTotal[USER_MESSAGE_BYTES_SENT]+rns->runningTotal[USER_MESSAGE_BYTES_RESENT]);
	if (uint64Denominator!=0&&rns->runningTotal[USER_MESSAGE_BYTES_SENT]/uint64Denominator>0)
	{
		doubleDenominator=((double) rns->runningTotal[USER_MESSAGE_BYTES_SENT]+(double) rns->runningTotal[USER_MESSAGE_BYTES_RESENT]);
		if(doubleDenominator!=0)
		{
			rns->packetlossTotal=(float)((double) rns->runningTotal[USER_MESSAGE_BYTES_RESENT]/doubleDenominator);
		}
	}

	rns->isLimitedByCongestionControl=statistics.isLimitedByCongestionControl;
	rns->BPSLimitByCongestionControl=statistics.BPSLimitByCongestionControl;
	rns->isLimitedByOutgoingBandwidthLimit=statistics.isLimitedByOutgoingBandwidthLimit;
	rns->BPSLimitByOutgoingBandwidthLimit=statistics.BPSLimitByOutgoingBandwidthLimit;

	return rns;
}
