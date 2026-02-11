concatenate_notes(unsigned char *cur_sha1,
		const unsigned char *new_sha1)
{
	char *cur_msg, *new_msg, *buf;
	unsigned long cur_len, new_len, buf_len;
	enum object_type cur_type, new_type;
	int ret;


	new_msg = read_sha1_file(new_sha1, &new_type, &new_len);
	if (!new_msg || !new_len || new_type != OBJ_BLOB) {
		free(new_msg);
		return 0;
	}
	cur_msg = read_sha1_file(cur_sha1, &cur_type, &cur_len);
	if (!cur_msg || !cur_len || cur_type != OBJ_BLOB) {
		free(cur_msg);
		free(new_msg);
		hashcpy(cur_sha1, new_sha1);
		return 0;
	}


	if (cur_msg[cur_len - 1] == '\n')
		cur_len--;


	buf_len = cur_len + 1 + new_len;
	buf = (char *) xmalloc(buf_len);
	memcpy(buf, cur_msg, cur_len);
	buf[cur_len] = '\n';
	memcpy(buf + cur_len + 1, new_msg, new_len);

	free(cur_msg);
	free(new_msg);


	ret = write_sha1_file(buf, buf_len, "blob", cur_sha1);
	free(buf);
	return ret;
}
