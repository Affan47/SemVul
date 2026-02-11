print_mac(const unsigned char *mac, int l)
{
	int j;

	for (j = 0; j < l; j++)
		printf("%02x%s", mac[j],
			(j==l-1) ? "" : ":");
}
