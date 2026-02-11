partition_delete (int nr)
{
	if ((parts<nr)||(nr<1)) {
		fprintf (stderr,"Could not delete partition %d.\n",nr);
		return -1;
	}

	nr--;

	if (nr==0) {
		if (htonl(rdb->rdb_PartitionList)==(ULONG)lastblock)
			lastblock--;

		rdb->rdb_PartitionList=pa[0]->pb_Next;

	} else {
		if (htonl(pa[nr-1]->pb_Next)==(ULONG)lastblock)
			lastblock--;
		pa[nr-1]->pb_Next=pa[nr]->pb_Next;
	}

	while (nr<parts) {
		pa[nr]=pa[nr+1];
		nr++;
	}
	pa[parts]	= NULL;

	parts--;
	return 0;
}
