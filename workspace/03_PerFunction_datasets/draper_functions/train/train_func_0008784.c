scsi_log_after (uae_u8 *data, int datalen, uae_u8 *sense, int senselen)
{
	int i;
	write_log (_T("DATAIN: %d\n"), datalen);
	for (i = 0; i < datalen && i < 100 && data; i++)
		write_log (_T("%s%02X"), i > 0 ? _T(".") : _T(""), data[i]);
	if (data && datalen > 0)
		write_log (_T("\n"));
	if (senselen > 0) {
		write_log (_T("SENSE: %d,"), senselen);
		for (i = 0; i < senselen && i < 32; i++) {
			write_log (_T("%s%02X"), i > 0 ? _T(".") : _T(""), sense[i]);
		}
		write_log (_T("\n"));
	}
}
