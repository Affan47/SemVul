UI_UTIL_read_pw_string(char *buf,int length,const char *prompt,int verify)
	{
	char buff[BUFSIZ];
	int ret;

	ret=UI_UTIL_read_pw(buf,buff,(length>BUFSIZ)?BUFSIZ:length,prompt,verify);
	OPENSSL_cleanse(buff,BUFSIZ);
	return(ret);
	}
