CheckUlDlRatio()
{

	if ( s_maxupload == 0xFFFF )
		s_maxupload = UNLIMITED;


	if ( s_maxdownload == 0xFFFF )
		s_maxdownload = UNLIMITED;

	if ( s_maxupload == UNLIMITED )
		return;


	if ( s_maxupload < 4  ) {
		if ( ( s_maxupload * 3 < s_maxdownload ) || ( s_maxdownload == 0 ) )
			s_maxdownload = s_maxupload * 3 ;
	} else if ( s_maxupload < 10  ) {
		if ( ( s_maxupload * 4 < s_maxdownload ) || ( s_maxdownload == 0 ) )
			s_maxdownload = s_maxupload * 4;
	}
}
