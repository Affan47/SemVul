diary_encode_uids (CamelDiscoDiary *diary,
                   GPtrArray *uids)
{
	gint i, status;

	status = camel_file_util_encode_uint32 (diary->file, uids->len);
	for (i = 0; status != -1 && i < uids->len; i++)
		status = camel_file_util_encode_string (diary->file, uids->pdata[i]);
	return status;
}
