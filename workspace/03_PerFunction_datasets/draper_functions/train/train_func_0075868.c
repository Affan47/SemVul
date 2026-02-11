ipmi_get_peakpower_consmpt_history(struct ipmi_intf * intf,
		IPMI_POWER_CONSUMP_HISTORY * pstPeakpower)
{
	uint8_t *rdata;
	int rc;
	rc = ipmi_mc_getsysinfo(intf, 0xec, 0, 0, sizeof(*pstPeakpower),
			pstPeakpower);
	if (rc < 0) {
		lprintf(LOG_ERR, "Error getting  peak power consumption history data.");
		return -1;
	} else if ((iDRAC_FLAG == IDRAC_12G) && (rc == LICENSE_NOT_SUPPORTED)) {
		lprintf(LOG_ERR,
				"FM001 : A required license is missing or expired");
		return -1;
	} else if ((rc == 0xc1) || (rc == 0xcb)) {
		lprintf(LOG_ERR, "Error getting peak power consumption history data: "
				"Command not supported on this system.");
		return -1;
	} else if (rc != 0) {
		lprintf(LOG_ERR, "Error getting peak power consumption history data: %s",
				val2str(rc, completion_code_vals));
		return -1;
	}
	if (verbose > 1) {
		rdata = (void *)pstPeakpower;
		printf("Peak power consmhistory  Data               : "
				"%x %x %x %x %x %x %x %x %x %x\n   "
				"%x %x %x %x %x %x %x %x %x %x %x %x %x\n\n",
				rdata[0], rdata[1], rdata[2], rdata[3],
				rdata[4], rdata[5], rdata[6], rdata[7],
				rdata[8], rdata[9], rdata[10], rdata[11],
				rdata[12], rdata[13], rdata[14], rdata[15],
				rdata[16], rdata[17], rdata[18], rdata[19],
				rdata[20], rdata[21], rdata[22], rdata[23]);
	}
# if WORDS_BIGENDIAN
	pstPeakpower->lastminutepower = BSWAP_16(pstPeakpower->lastminutepower);
	pstPeakpower->lasthourpower = BSWAP_16(pstPeakpower->lasthourpower);
	pstPeakpower->lastdaypower = BSWAP_16(pstPeakpower->lastdaypower);
	pstPeakpower->lastweakpower = BSWAP_16(pstPeakpower->lastweakpower);
	pstPeakpower->lastminutepowertime = BSWAP_32(pstPeakpower->lastminutepowertime);
	pstPeakpower->lasthourpowertime = BSWAP_32(pstPeakpower->lasthourpowertime);
	pstPeakpower->lastdaypowertime = BSWAP_32(pstPeakpower->lastdaypowertime);
	pstPeakpower->lastweekpowertime = BSWAP_32(pstPeakpower->lastweekpowertime);
#endif
	return 0;
}
