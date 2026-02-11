fake_pcap_canonical_dlt(int dlt, bool)
{
    if (dlt == FAKE_DLT_HOST_RAW)
	return FAKE_DLT_RAW;
    else
	return dlt;
}
