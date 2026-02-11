http_PutStatus(struct http *to, int status)
{

	assert(status >= 0 && status <= 999);
	to->status = status;
}
