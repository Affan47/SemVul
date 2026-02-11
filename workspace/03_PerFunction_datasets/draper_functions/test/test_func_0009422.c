netlookup(char *name, uint32_t *ip)
{
	struct hostent *he;

	if(parseip(name, ip) >= 0)
		return 0;


	taskstate("netlookup");
	if((he = gethostbyname(name)) != 0){
		*ip = *(uint32_t*)he->h_addr;
		taskstate("netlookup succeeded");
		return 0;
	}

	taskstate("netlookup failed");
	return -1;
}
