unformat_message(xdrproc_t type, unsigned size,
			struct mrpc_message *msg, void **result)
{
	void *buf;
	mrpc_status_t ret;

	if (size && result == NULL)
		return MINIRPC_ENCODING_ERR;
	buf=mrpc_alloc_argument(size);
	ret=unserialize(type, msg->data, msg->hdr.datalen, buf, size);
	if (ret) {
		mrpc_free_argument(NULL, buf);
		return ret;
	}
	if (result != NULL)
		*result=buf;
	return MINIRPC_OK;
}
