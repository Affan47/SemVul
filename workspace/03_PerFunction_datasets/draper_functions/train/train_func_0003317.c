blob_register_pack(char c, blob_fmt_cb fmt_cb)
{
	if (blob_ascii_fmt[(int)c] == NULL) {
		blob_ascii_fmt[(int)c] = fmt_cb;
		return (0);
	}
	return (-1);
}
