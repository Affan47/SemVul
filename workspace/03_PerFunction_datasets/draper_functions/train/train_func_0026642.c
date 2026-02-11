bm_create( int bpp, int w, int h, void *data, int flags )
{
	if (bpp == 8) {
		Assert(flags & BMP_AABITMAP);
	} else {
		Assert( (bpp == 16) || (bpp == 24) || (bpp == 32) );
	}

	if ( !bm_inited ) bm_init();

	int n = -1;

	for (int i = MAX_BITMAPS-1; i >= 0; i-- ) {
		if ( bm_bitmaps[i].type == BM_TYPE_NONE )	{
			n = i;
			break;
		}
	}

	Assert( n > -1 );


	if ( n == -1 )
		return -1;


	if (data == NULL) {
		Int3();
		return -1;
	}

	memset( &bm_bitmaps[n], 0, sizeof(bitmap_entry) );

	sprintf( bm_bitmaps[n].filename, "TMP%dx%d+%d", w, h, bpp );
	bm_bitmaps[n].type = BM_TYPE_USER;
	bm_bitmaps[n].comp_type = BM_TYPE_NONE;
	bm_bitmaps[n].palette_checksum = 0;

	bm_bitmaps[n].bm.w = (short) w;
	bm_bitmaps[n].bm.h = (short) h;
	bm_bitmaps[n].bm.rowsize = (short) w;
	bm_bitmaps[n].bm.bpp = (ubyte) bpp;
	bm_bitmaps[n].bm.flags = (ubyte) flags;
	bm_bitmaps[n].bm.data = 0;
	bm_bitmaps[n].bm.palette = NULL;

	bm_bitmaps[n].info.user.bpp = (ubyte)bpp;
	bm_bitmaps[n].info.user.data = data;
	bm_bitmaps[n].info.user.flags = (ubyte)flags;

	bm_bitmaps[n].signature = Bm_next_signature++;

	bm_bitmaps[n].handle = bm_get_next_handle() * MAX_BITMAPS + n;
	bm_bitmaps[n].last_used = -1;
	bm_bitmaps[n].mem_taken = (w * h * (bpp >> 3));

	bm_bitmaps[n].load_count++;

	bm_update_memory_used( n, bm_bitmaps[n].mem_taken );

	gr_bm_create(n);

	return bm_bitmaps[n].handle;
}
