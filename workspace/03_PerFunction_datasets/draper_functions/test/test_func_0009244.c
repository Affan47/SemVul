in_cksum(const u_int16_t *w, int len)
{
	int		nleft = len, sum = 0;
	u_int16_t       answer;

	while (nleft > 1) {
		sum += *w++;
		nleft -= 2;
	}
	if (nleft == 1)
		sum += htons(*(u_char *) w << 8);

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;
	return answer;
}
