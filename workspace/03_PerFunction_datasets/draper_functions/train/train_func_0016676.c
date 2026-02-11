checkForIni(int argc, _TCHAR* argv[])
{
	int index;
	for(index = 0; index < (argc - 1); index++) {
		if(_tcsicmp(argv[index], INI) == 0) {
        	return argv[++index];
        }
	}
	return NULL;
}
