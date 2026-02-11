check_tentative_tls(ioa_socket_raw fd)
{
	TURN_TLS_TYPE ret = TURN_TLS_NO;

	char s[12];
	int len = 0;

	do {
		len = (int)recv(fd, s, sizeof(s), MSG_PEEK);
	} while (len < 0 && (errno == EINTR));

	if(len>0 && ((size_t)len == sizeof(s))) {
		if((s[0]==22)&&(s[1]==3)&&(s[5]==1)&&(s[9]==3)) {
			char max_supported = (char)(TURN_TLS_TOTAL-2);
			if(s[10] >= max_supported)
				ret = (TURN_TLS_TYPE)((((int)TURN_TLS_TOTAL)-1));
			else
				ret = (TURN_TLS_TYPE)(s[10]+1);
		} else if((s[2]==1)&&(s[3]==3)) {
			ret = TURN_TLS_SSL23;
		} else if((s[2]==1)&&(s[3]==0)&&(s[4]==2)) {
			ret = TURN_TLS_SSL23;
		}
	}

	return ret;
}
