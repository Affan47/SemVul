binary2string(char* buf, char* maxp, void* value, size_t len, int depth)
{
	int baselen;
	int truelen = 0;

	(void)depth;
	baselen = B64_stringlen(len) + 1;

	if ( buf + baselen > maxp){
		cl_log(LOG_ERR, "binary2string: out of bounary");
		return -1;
	}

	truelen = binary_to_base64(value, len, buf, baselen);

	return truelen;
}
