send_stream(krb5_context context, struct host *host)
{
    ssize_t len;

    len = krb5_net_write(context, &host->fd, host->data.data, host->data.length);

    if (len < 0)
	return errno;
    else if (len < host->data.length) {
	host->data.length -= len;
	memmove(host->data.data, ((uint8_t *)host->data.data) + len, host->data.length - len);
	return -1;
    } else {
	krb5_data_free(&host->data);
	return 0;
    }
}
