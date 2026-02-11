process_entry_path(
	const char* entry_path,
	const git_oid *note_oid,
	int (*note_cb)(git_note_data *note_data, void *payload),
	void *payload)
{
	int error = -1;
	size_t i = 0, j = 0, len;
	git_buf buf = GIT_BUF_INIT;
	git_note_data note_data;

	if ((error = git_buf_puts(&buf, entry_path)) < 0)
		goto cleanup;

	len = git_buf_len(&buf);

	while (i < len) {
		if (buf.ptr[i] == '/') {
			i++;
			continue;
		}

		if (git__fromhex(buf.ptr[i]) < 0) {

			goto cleanup;
		}

		if (i != j)
			buf.ptr[j] = buf.ptr[i];

		i++;
		j++;
	}

	buf.ptr[j] = '\0';
	buf.size = j;

	if (j != GIT_OID_HEXSZ) {

		goto cleanup;
	}

	if ((error = git_oid_fromstr(
			&note_data.annotated_object_oid, buf.ptr)) < 0)
		goto cleanup;

	git_oid_cpy(&note_data.blob_oid, note_oid);

	if (note_cb(&note_data, payload))
		error = GIT_EUSER;

cleanup:
	git_buf_free(&buf);
	return error;
}
