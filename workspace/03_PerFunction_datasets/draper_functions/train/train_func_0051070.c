tconInfoFree(struct cifs_tcon *buf_to_free)
{
	if (buf_to_free == NULL) {
		cifs_dbg(FYI, "Null buffer passed to tconInfoFree\n");
		return;
	}
	atomic_dec(&tconInfoAllocCount);
	kfree(buf_to_free->nativeFileSystem);
	if (buf_to_free->password) {
		memset(buf_to_free->password, 0, strlen(buf_to_free->password));
		kfree(buf_to_free->password);
	}
	kfree(buf_to_free);
}
