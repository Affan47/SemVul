createHostPort (const char* host_, int port_)
{


	struct hostent* hp = 0;

	if (strlen (host_) == 0) {
		m_address.sin_addr.s_addr = htonl(INADDR_ANY);
		goto done;
	}

	if ((hp = gethostbyname (host_)) == NULL) {
		setstate (Address::badbit);
		errno = h_errno;
		EL((ASSAERR,"gethostbyname (\"%s\") failed\n", host_));
		return;
	}
	memcpy ((char*) &m_address.sin_addr, hp->h_addr_list[0], hp->h_length);

done:
	m_address.sin_family = AF_INET;
   	m_address.sin_port = port_;
}
