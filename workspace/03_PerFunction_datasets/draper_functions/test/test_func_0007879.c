SendRawPacket (int sockfd, void *buff, int len) {
	int slen;

	if ((slen = write(sockfd, buff, len)) != len) {
		printf("Sent %d bytes\n", slen);
		return 0;
	}
	return 1;
}
