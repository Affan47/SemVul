load_mib2nut(const char *mib)
{
	int	i;
	char	buf[LARGEBUF];
	mib2nut_info_t *m2n = NULL;

	upsdebugx(2, "SNMP UPS driver : entering load_mib2nut(%s)", mib);


	if (!strcmp(mib, "auto"))
	{
		upsdebugx(1, "trying the new match_sysoid() method");
		m2n = match_sysoid();
	}


	if (m2n == NULL)
	{
		for (i = 0; mib2nut[i] != NULL; i++) {

			if (strcmp(mib, "auto") && strcmp(mib, mib2nut[i]->mib_name)) {
				continue;
			}
			upsdebugx(1, "load_mib2nut: trying classic method with '%s' mib", mib2nut[i]->mib_name);


			if (!nut_snmp_get_str(mib2nut[i]->oid_auto_check, buf, sizeof(buf), NULL)) {
				continue;
			}

			m2n = mib2nut[i];
			break;
		}
	}


	if (m2n != NULL)
	{
		snmp_info = m2n->snmp_info;
		OID_pwr_status = m2n->oid_pwr_status;
		mibname = m2n->mib_name;
		mibvers = m2n->mib_version;
		upsdebugx(1, "load_mib2nut: using %s mib", mibname);
		return TRUE;
	}


	if (strcmp(mib, "auto") != 0) {
		fatalx(EXIT_FAILURE, "Unknown mibs value: %s", mib);
	} else {
		fatalx(EXIT_FAILURE, "No supported device detected");
	}
}
