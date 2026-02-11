get_default_protocol_port(const char* scheme, size_t slen)
{
	if(scheme && (slen>0)) {
		switch(slen) {
		case 3:
			if(!memcmp("ftp",scheme,3))
				return 21;
			if(!memcmp("svn",scheme,3))
				return 3690;
			if(!memcmp("ssh",scheme,4))
				return 22;
			if(!memcmp("sip",scheme,3))
				return 5060;
			break;
		case 4:
			if(!memcmp("http",scheme,4))
				return 80;
			if(!memcmp("ldap",scheme,4))
				return 389;
			if(!memcmp("sips",scheme,4))
				return 5061;
			if(!memcmp("turn",scheme,4))
				return 3478;
			if(!memcmp("stun",scheme,4))
				return 3478;
			break;
		case 5:
			if(!memcmp("https",scheme,5))
				return 443;
			if(!memcmp("ldaps",scheme,5))
				return 636;
			if(!memcmp("turns",scheme,5))
				return 5349;
			if(!memcmp("stuns",scheme,5))
				return 5349;
			break;
		case 6:
			if(!memcmp("telnet",scheme,6))
				return 23;
			if(!memcmp("radius",scheme,6))
				return 1645;
			break;
		case 7:
			if(!memcmp("svn+ssh",scheme,7))
				return 22;
			break;
		default:
			return 0;
		};
	}
	return 0;
}
