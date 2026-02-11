read_net_etcp(struct stats_net_etcp *st_net_etcp)
{
	FILE *fp;
	char line[1024];
	int sw = FALSE;

	if ((fp = fopen(NET_SNMP, "r")) == NULL)
		return;

	while (fgets(line, 1024, fp) != NULL) {

		if (!strncmp(line, "Tcp:", 4)) {
			if (sw) {
				sscanf(line + 4, "%*u %*u %*u %*d %*u %*u "
				       "%lu %lu %*u %*u %*u %lu %lu %lu",
				       &st_net_etcp->AttemptFails,
				       &st_net_etcp->EstabResets,
				       &st_net_etcp->RetransSegs,
				       &st_net_etcp->InErrs,
				       &st_net_etcp->OutRsts);

				break;
			}
			else {
				sw = TRUE;
			}
		}
	}

	fclose(fp);
}
