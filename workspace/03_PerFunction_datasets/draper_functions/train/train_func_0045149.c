seek_data_cb(void *user_data, curl_off_t offset, int origin)
{
	struct upload_buffer *ub = user_data;

	switch (origin) {
	case SEEK_SET:
		ub->pos = offset;
		break;
	case SEEK_CUR:
		ub->pos += offset;
		break;
	case SEEK_END:
		ub->pos = ub->len + offset;
		break;
	default:
		return 1;
	}

	return 0;
}
