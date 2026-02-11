html_status(int code, const char *msg, int more_headers)
{
	htmlf("Status: %d %s\n", code, msg);
	if (!more_headers)
		html("\n");
}
