bm_lock_user( int handle, int bitmapnum, bitmap_entry *be, bitmap *bmp, ubyte bpp, ubyte flags )
{

	bm_free_data( bitmapnum );

	if ((bpp != be->info.user.bpp) && !(flags & BMP_AABITMAP))
		bpp = be->info.user.bpp;

	switch ( bpp ) {
		case 32:
			bmp->bpp = bpp;
			bmp->flags = be->info.user.flags;
			bmp->data = (ptr_u)be->info.user.data;
			break;

		case 24:
			bmp->bpp = bpp;
			bmp->flags = be->info.user.flags;
			bmp->data = (ptr_u)be->info.user.data;
			break;

		case 16:
			bmp->bpp = bpp;
			bmp->flags = be->info.user.flags;
			bmp->data = (ptr_u)be->info.user.data;
			break;

		case 8:
			Assert(flags & BMP_AABITMAP);
			bmp->bpp = bpp;
			bmp->flags = be->info.user.flags;
			bmp->data = (ptr_u)be->info.user.data;
			break;

		 default:
			Error( LOCATION, "Unhandled user bitmap conversion from %d to %d bpp", be->info.user.bpp, bmp->bpp );
			break;
	}

	bm_convert_format( bitmapnum, bmp, bpp, flags );
}
