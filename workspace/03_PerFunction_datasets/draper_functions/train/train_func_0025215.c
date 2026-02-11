write_data (apr_socket_t *sock, const void *str, apr_size_t size)
{
	apr_size_t prevsize = size;
	apr_status_t statcode;

	if ((statcode = apr_socket_send (sock, str, &size)) != APR_SUCCESS) {
		ap_log_error (APLOG_MARK, APLOG_ERR, STATCODE_AND_SERVER (statcode), "write_data failed");
		return -1;
	}

	return (prevsize == size) ? size : -1;
}
