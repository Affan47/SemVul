bm_reload(int bitmap_handle, char* filename)
{
	if ( !bm_inited )
		bm_init();


	if ( (filename == NULL) || (strlen(filename) <= 0) )
		return -1;

	int bitmapnum = bitmap_handle % MAX_BITMAPS;

	if ( bm_bitmaps[bitmapnum].type == BM_TYPE_NONE )
		return -1;

	if ( bm_bitmaps[bitmapnum].ref_count )
	{
		nprintf(("BmpMan", "Trying to reload a bitmap that is still locked. Filename: %s, ref_count: %d", bm_bitmaps[bitmapnum].filename, bm_bitmaps[bitmapnum].ref_count));
		return -1;
	}

	strncpy(bm_bitmaps[bitmapnum].filename, filename, MAX_FILENAME_LEN);
	return bitmap_handle;
}
