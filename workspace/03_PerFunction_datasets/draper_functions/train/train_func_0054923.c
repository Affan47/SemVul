match_sysoid()
{
	char sysOID_buf[LARGEBUF];
	oid device_sysOID[MAX_OID_LEN];
	size_t device_sysOID_len = MAX_OID_LEN;
	oid mib2nut_sysOID[MAX_OID_LEN];
	size_t mib2nut_sysOID_len = MAX_OID_LEN;
	int i;


	if (nut_snmp_get_str(SYSOID_OID, sysOID_buf, sizeof(sysOID_buf), NULL))
	{
		upsdebugx(1, "match_sysoid: device sysOID value = %s", sysOID_buf);


		if (!read_objid(sysOID_buf, device_sysOID, &device_sysOID_len))
		{
			upsdebugx(2, "match_sysoid: can't build device_sysOID %s: %s",
				sysOID_buf, snmp_api_errstring(snmp_errno));

			return FALSE;
		}


		for (i = 0; mib2nut[i] != NULL; i++)
		{
			upsdebugx(1, "match_sysoid: checking MIB %s", mib2nut[i]->mib_name);

			if (mib2nut[i]->sysOID == NULL)
				continue;


			memset(mib2nut_sysOID, 0, MAX_OID_LEN);
			mib2nut_sysOID_len = MAX_OID_LEN;

			if (!read_objid(mib2nut[i]->sysOID, mib2nut_sysOID, &mib2nut_sysOID_len))
			{
				upsdebugx(2, "match_sysoid: can't build OID %s: %s",
					sysOID_buf, snmp_api_errstring(snmp_errno));


				continue;
			}

			upsdebugx(1, "match_sysoid: comparing %s with %s", sysOID_buf, mib2nut[i]->sysOID);
			if (!netsnmp_oid_equals(device_sysOID, device_sysOID_len, mib2nut_sysOID, mib2nut_sysOID_len))
			{
				upsdebugx(2, "match_sysoid: sysOID matches MIB '%s'!", mib2nut[i]->mib_name);
				return mib2nut[i];
			}
		}

		upslogx(LOG_ERR, "No matching MIB found for sysOID '%s'!\n" \
			"Please report it to NUT developers, with an 'upsc' output for your device.\n" \
			"Going back to the classic MIB detection method.",
			sysOID_buf);
	}
	else
		upsdebugx(2, "Can't get sysOID value");

	return NULL;
}
