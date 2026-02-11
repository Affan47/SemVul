ldns_tcp_send_query(ldns_buffer *qbin, int sockfd,
                    const struct sockaddr_storage *to, socklen_t tolen)
{
	uint8_t *sendbuf;
	ssize_t bytes;


	sendbuf = LDNS_XMALLOC(uint8_t, ldns_buffer_position(qbin) + 2);
	if(!sendbuf) return 0;
	ldns_write_uint16(sendbuf, ldns_buffer_position(qbin));
	memcpy(sendbuf + 2, ldns_buffer_begin(qbin), ldns_buffer_position(qbin));

	bytes = sendto(sockfd, (void*)sendbuf,
			ldns_buffer_position(qbin) + 2, 0, (struct sockaddr *)to, tolen);

        LDNS_FREE(sendbuf);

	if (bytes == -1 || (size_t) bytes != ldns_buffer_position(qbin) + 2 ) {
		return 0;
	}
	return bytes;
}
