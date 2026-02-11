bm_page_in_texture( int bitmapnum, int nframes )
{
	int i;
	int n = bitmapnum % MAX_BITMAPS;

	if (bitmapnum < 0)
		return;

	Assertion( (bm_bitmaps[n].handle == bitmapnum), "bitmapnum = %i, n = %i, bm_bitmaps[n].handle = %i", bitmapnum, n, bm_bitmaps[n].handle );

	if (nframes <= 0) {
		if ( (bm_bitmaps[n].type == BM_TYPE_ANI) || (bm_bitmaps[n].type == BM_TYPE_EFF) )
			nframes = bm_bitmaps[n].info.ani.num_frames;
		else
			nframes = 1;
	}

	for (i = 0; i < nframes;i++) {
		bm_bitmaps[n+i].preloaded = 1;

		bm_bitmaps[n+i].preload_count++;

		bm_bitmaps[n+i].used_flags = BMP_TEX_OTHER;


		switch (bm_bitmaps[n+i].comp_type)
		{
			case BM_TYPE_NONE:
				continue;

			case BM_TYPE_DXT1:
				bm_bitmaps[n+i].used_flags = BMP_TEX_DXT1;
				continue;

			case BM_TYPE_DXT3:
				bm_bitmaps[n+i].used_flags = BMP_TEX_DXT3;
				continue;

			case BM_TYPE_DXT5:
				bm_bitmaps[n+i].used_flags = BMP_TEX_DXT5;
				continue;

			case BM_TYPE_CUBEMAP_DXT1:
			case BM_TYPE_CUBEMAP_DXT3:
			case BM_TYPE_CUBEMAP_DXT5:
				bm_bitmaps[n+i].used_flags = BMP_TEX_CUBEMAP;
				continue;
		}
	}
}
