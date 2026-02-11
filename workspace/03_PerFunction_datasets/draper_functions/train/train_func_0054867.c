parse_ircomm_ttp(GNetBuf *buf, GString *str)
{
	int	len;
	guint8 clen;


	len = g_netbuf_get_len(buf);
	if(len == 0)
		return;

	clen = buf->data[0];

	g_netbuf_pull(buf, 1);

	if (clen) {
		g_string_append(str, "\n\tIrCOMM ");
		parse_ircomm_params(clen, buf, str);
	} else
		g_string_append(str, "IrCOMM ");
}
