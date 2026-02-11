aino_from_buf (a_inode *base, uae_u8 *buf, long off)
{
	uae_u32 mode;
	a_inode *aino = xcalloc (a_inode, 1);
	TCHAR *s;

	mode = do_get_mem_long ((uae_u32 *)(buf + 1));
	buf += 5;
	aino->aname = au ((char*)buf);
	buf += 257;
	s = au ((char*)buf);
	aino->nname = build_nname (base->nname, s);
	xfree (s);
	buf += 257;
	aino->comment = *buf != '\0' ? au ((char*)buf) : 0;
	fsdb_fill_file_attrs (base, aino);
	aino->amigaos_mode = mode;
	aino->has_dbentry = 1;
	aino->dirty = 0;
	aino->db_offset = off;
	return aino;
}
