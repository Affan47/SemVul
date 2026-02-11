Load(void){
	if (!func_load) return TRUE;

	string basepath;
	string::size_type pos=basepath.find_last_of(FILE_SEPARATOR);
	if (pos==string::npos){
		basepath=path+FILE_SEPARATOR;
	}else{
		basepath=path.substr(0, pos+1);
	}

	long len=basepath.size();
	MEMORY_HANDLE h=(MEMORY_HANDLE)SHIORI_MALLOC(len);
	if (!h) return false;
	basepath.copy((char *)h, len);
	GetFactory().GetLogger().GetStream(LOG_INFO) << "[SAORI Native] load(" << basepath << ")." << endl;
	return (0!=(func_load)(h,len));
}
