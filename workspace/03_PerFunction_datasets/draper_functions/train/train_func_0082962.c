in_cksum(const u_short *addr, int len)
{
	int nleft = len;
	const u_short *w = addr;
	u_short answer;
	int sum = 0;


	while (nleft > 1)  {
		sum += *w++;
		nleft -= 2;
	}


	if (nleft == 1)
		sum += htons(*(u_char *)w << 8);

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return (answer);
}
