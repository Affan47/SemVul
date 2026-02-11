getNMbuf()
{
	register Buffer	*delbuf = buf_exists(ask_buf(curbuf,
		ALLOW_OLD | ALLOW_INDEX));

	if (delbuf->b_modified)
		confirm("%s modified, are you sure? ", delbuf->b_name);
	return delbuf;
}
