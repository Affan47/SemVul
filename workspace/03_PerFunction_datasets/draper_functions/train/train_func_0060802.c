ATR_GetDefaultProtocol(ATR_t * atr, int *protocol)
{
	int i;


	*protocol = PROTOCOL_UNSET;

	for (i=0; i<ATR_MAX_PROTOCOLS; i++)
		if (atr->ib[i][ATR_INTERFACE_BYTE_TD].present && (PROTOCOL_UNSET == *protocol))
		{

			*protocol = atr->ib[i][ATR_INTERFACE_BYTE_TD].value & 0x0F;
			DEBUG_COMM2("default protocol: T=%d", *protocol);
		}


	if (atr->ib[1][ATR_INTERFACE_BYTE_TA].present)
	{
		*protocol = atr->ib[1][ATR_INTERFACE_BYTE_TA].value & 0x0F;
		DEBUG_COMM2("specific mode found: T=%d", *protocol);
	}

	if (PROTOCOL_UNSET == *protocol)
	{
		DEBUG_INFO("no default protocol found in ATR. Using T=0");
		*protocol = ATR_PROTOCOL_TYPE_T0;
	}

	return ATR_OK;
}
