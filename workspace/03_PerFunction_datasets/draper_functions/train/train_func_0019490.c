avdtp_error_init(struct avdtp_error *err, uint8_t category, int id)
{
	err->category = category;

	if (category == AVDTP_ERRNO)
		err->err.posix_errno = id;
	else
		err->err.error_code = id;
}
