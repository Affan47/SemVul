ps_get_parent_ps_type_by_uuid(TSS_UUID *uuid, UINT32 *type)
{
	int fd;
	TSS_RESULT result;

	if ((result = get_file(&fd)))
		return result;

	result = psfile_get_parent_ps_type(fd, uuid, type);

	put_file(fd);

        return result;
}
