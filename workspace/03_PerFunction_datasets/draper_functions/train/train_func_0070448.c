indexid(long index)
{
	FILEID id;

	id = (FILEID) index;

	if ((index < 0) || (id > lastid))
		return FILEID_NONE;
	return id;
}
