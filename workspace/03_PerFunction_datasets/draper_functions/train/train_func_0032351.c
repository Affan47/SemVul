check_self(str* host, unsigned short port, unsigned short proto)
{
	if (grep_sock_info(host, port, proto)) goto found;

	if (grep_aliases(host->s, host->len, port, proto)==0){
		LM_DBG("host != me\n");
		return 0;
	}
found:
	return 1;
}
