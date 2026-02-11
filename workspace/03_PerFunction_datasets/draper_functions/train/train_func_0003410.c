cfwrite_string_len(const char *buf, CFILE *file)
{
	int len = strlen(buf);

	if(!cfwrite_int(len, file)){
		return 0;
	}
	if (len){
		return cfwrite(buf,len,1,file);
	}

	return 1;
}
