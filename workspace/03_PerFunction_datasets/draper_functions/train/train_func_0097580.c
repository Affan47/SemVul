CanonicalPath(const wstring &path){
	wstring ret=path;
	unsigned int len=ret.length();
	for (unsigned int i=0; i<len; i++)
		if (ret[i]==BADSEPARATOR) ret[i]=SEPARATOR;
	return ret;
}
