errorHandler(int level, const string &flag)
{
	if( level <= 0 ){
		perror(flag.c_str());
		return 1;
	}
	else return 0;
}
