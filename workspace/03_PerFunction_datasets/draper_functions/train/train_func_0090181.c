string2mode(const char *str_mode)
{

	mode_t mode = 0;


	if( strlen( str_mode ) < 9 ) {

		return 0;
	}


	switch( str_mode[0] ) {
		case '-' :
			mode |= S_IFREG;
			break;
		case 'd' :
			mode |= S_IFDIR;
			break;
#ifndef WIN32
		case 'l' :
			mode |= S_IFLNK;
			break;
		case 'x' :
			mode |= S_IFCHR;
			break;
		default:
			mode |= S_IFIFO;
			break;
#endif
	}


#ifndef WIN32


	if( str_mode[1] == 'r' )
		mode |= S_IRUSR;
	if( str_mode[2] == 'w' )
		mode |= S_IWUSR;
	if( str_mode[3] == 'x' )
		mode |= S_IXUSR;


	if( str_mode[4] == 'r' )
		mode |= S_IRGRP;
	if( str_mode[5] == 'w' )
		mode |= S_IWGRP;
	if( str_mode[6] == 'x' )
		mode |= S_IXGRP;


	if( str_mode[7] == 'r' )
		mode |= S_IROTH;
	if( str_mode[8] == 'w' )
		mode |= S_IWOTH;
	if( str_mode[9] == 'x' )
		mode |= S_IXOTH;

#else

	if( str_mode[1] == 'r' )
		mode |= _S_IREAD;
	if( str_mode[2] == 'w' )
		mode |= _S_IWRITE;
#endif

	return mode;
}
