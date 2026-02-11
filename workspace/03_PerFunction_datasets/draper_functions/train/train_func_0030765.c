print_ipc(const u_char *param, int paramlen, const u_char *data, int datalen)
{
    if (paramlen)
	smb_fdata(param, "Command=[w]\nStr1=[S]\nStr2=[S]\n", param + paramlen,
	    unicodestr);
    if (datalen)
	smb_fdata(data, "IPC ", data + datalen, unicodestr);
}
