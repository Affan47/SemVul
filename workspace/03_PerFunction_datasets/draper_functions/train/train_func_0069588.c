detail_print(const rad_listen_t *this, char *buffer, size_t bufsize)
{
	if (!this->server) {
		return snprintf(buffer, bufsize, "%s",
				((listen_detail_t *)(this->data))->filename);
	}

	return snprintf(buffer, bufsize, "detail file %s as server %s",
			((listen_detail_t *)(this->data))->filename,
			this->server);
}
