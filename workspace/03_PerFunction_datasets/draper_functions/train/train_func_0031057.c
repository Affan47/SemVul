getcwd() {
	static char* c = NULL;
	if(c==NULL) c = new char[512];
	if(!getcwd(c, 512)) {};
	return c;
}
