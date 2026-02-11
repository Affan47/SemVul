cstp_bye(struct openconnect_info *vpninfo, char *reason)
{
	unsigned char *bye_pkt;
	int reason_len;


	if (!vpninfo->https_ssl)
		return 0;

	reason_len = strlen(reason);
	bye_pkt = malloc(reason_len + 8);
	if (!bye_pkt)
		return -ENOMEM;

	memcpy(bye_pkt, data_hdr, 8);
	memcpy(bye_pkt + 8, reason, reason_len);

	bye_pkt[4] = reason_len >> 8;
	bye_pkt[5] = reason_len & 0xff;
	bye_pkt[6] = AC_PKT_DISCONN;

	SSL_write(vpninfo->https_ssl, bye_pkt, reason_len + 8);
	free(bye_pkt);

	vpninfo->progress(vpninfo, PRG_INFO,
			  "Send BYE packet: %s\n", reason);

	return 0;
}
