zstream_seterr(git_zstream *zs)
{
	if (zs->zerr == Z_OK || zs->zerr == Z_STREAM_END)
		return 0;

	if (zs->zerr == Z_MEM_ERROR)
		giterr_set_oom();
	else if (zs->z.msg)
		giterr_set(GITERR_ZLIB, zs->z.msg);
	else
		giterr_set(GITERR_ZLIB, "Unknown compression error");

	return -1;
}
