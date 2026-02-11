ntlmssp_input_av_pairs(NTLMSSP* ntlmssp, STREAM* s)
{
	AV_ID AvId;
	uint16 AvLen;
	uint8* value;
	AV_PAIRS* av_pairs = ntlmssp->av_pairs;

	do
	{
		value = NULL;
		stream_read_uint16(s, AvId);
		stream_read_uint16(s, AvLen);

		if (AvLen > 0)
		{
			if (AvId != MsvAvFlags)
			{
				value = xmalloc(AvLen);
				stream_read(s, value, AvLen);
			}
			else
			{
				stream_read_uint32(s, av_pairs->Flags);
			}
		}

		switch (AvId)
		{
			case MsvAvNbComputerName:

				av_pairs->NbComputerName.length = AvLen;
				av_pairs->NbComputerName.value = value;
				break;

			case MsvAvNbDomainName:

				av_pairs->NbDomainName.length = AvLen;
				av_pairs->NbDomainName.value = value;
				break;

			case MsvAvDnsComputerName:

				av_pairs->DnsComputerName.length = AvLen;
				av_pairs->DnsComputerName.value = value;
				break;

			case MsvAvDnsDomainName:

				av_pairs->DnsDomainName.length = AvLen;
				av_pairs->DnsDomainName.value = value;
				break;

			case MsvAvDnsTreeName:

				av_pairs->DnsTreeName.length = AvLen;
				av_pairs->DnsTreeName.value = value;
				break;

			case MsvAvTimestamp:

				av_pairs->Timestamp.length = AvLen;
				av_pairs->Timestamp.value = value;
				break;

			case MsvAvRestrictions:

				av_pairs->Restrictions.length = AvLen;
				av_pairs->Restrictions.value = value;
				break;

			case MsvAvTargetName:

				av_pairs->TargetName.length = AvLen;
				av_pairs->TargetName.value = value;
				break;

			case MsvChannelBindings:

				av_pairs->ChannelBindings.length = AvLen;
				av_pairs->ChannelBindings.value = value;
				break;

			default:
				if (value != NULL)
					xfree(value);
				break;
		}
	}
	while(AvId != MsvAvEOL);
}
