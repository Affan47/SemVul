bm_is_render_target(int bitmap_id)
{
	int n = bitmap_id % MAX_BITMAPS;

	Assert(bitmap_id == bm_bitmaps[n].handle);

	if ( !((bm_bitmaps[n].type == BM_TYPE_RENDER_TARGET_STATIC) || (bm_bitmaps[n].type == BM_TYPE_RENDER_TARGET_DYNAMIC)) ) {
		return 0;
	}

	return bm_bitmaps[n].type;
}
