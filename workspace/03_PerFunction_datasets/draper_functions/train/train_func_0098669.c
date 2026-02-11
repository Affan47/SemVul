FormatLine(
char* into, const char* dir, const char* type, unsigned int reliableMessageNumber, unsigned int frame, const char* idToPrint
, const BitSize_t bitLen, unsigned long long time, const SystemAddress& local, const SystemAddress& remote,
unsigned int splitPacketId, unsigned int splitPacketIndex, unsigned int splitPacketCount, unsigned int orderingIndex)
{
	char str1[64], str2[62];
	local.ToString(true, str1);
	remote.ToString(true, str2);
	char localtime[128];
	GetLocalTime(localtime);
	char str3[64];
	if (reliableMessageNumber==(unsigned int)-1)
	{
		str3[0]='N';
		str3[1]='/';
		str3[2]='A';
		str3[3]=0;
	}
	else
	{
		sprintf(str3,"%5u",reliableMessageNumber);
	}

	sprintf(into, "%s,%s%s,%s,%s,%5u,%s,%u,%" PRINTF_64_BIT_MODIFIER "u,%s,%s,%i,%i,%i,%i,%s,"
					, localtime
					, prefix
					, dir
					, type
					, str3
					, frame
					, idToPrint
					, bitLen
					, time
					, str1
					, str2
					, splitPacketId
					, splitPacketIndex
					, splitPacketCount
					, orderingIndex
					, suffix
					);
}
