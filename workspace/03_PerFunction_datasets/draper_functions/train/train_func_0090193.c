file_info_set_fields_from_copy_binary(
	const char *buf, int residual, void *vinfo)
{
	struct db_inode_cksum_arg *info = vinfo;
	uint16_t num_fields;

	COPY_BINARY(num_fields, buf, residual,
	    "pgsql_file_info_load: field number");
	num_fields = ntohs(num_fields);
	if (num_fields < 3)
		gflog_fatal(GFARM_MSG_1000445,
		    "pgsql_file_info_load: fields = %d", num_fields);

	info->inum = get_int64_from_copy_binary(&buf, &residual);
	info->type = get_string_from_copy_binary(&buf, &residual);
	info->sum = get_string_from_copy_binary(&buf, &residual);
	info->len = strlen(info->sum);
}
