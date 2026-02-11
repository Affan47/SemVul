setup_prod(void)
{
	BLOCK_ZERO(&apiret, sizeof(apiret));
	apiret.sin_family = AF_INET;
	apiret.sin_addr.s_addr = htonl(INADDR_ANY);
	apiret.sin_port = 0;
	if  ((prodsock = socket(AF_INET, SOCK_DGRAM, udpproto)) < 0)
		return;
	if  (bind(prodsock, (struct sockaddr *) &apiret, sizeof(apiret)) < 0)  {
		close(prodsock);
		prodsock = -1;
	}
}
