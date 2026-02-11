bm_get_filename(int handle)
{
	int n;

	n = handle % MAX_BITMAPS;
	Assert(bm_bitmaps[n].handle == handle);
	return bm_bitmaps[n].filename;
}
