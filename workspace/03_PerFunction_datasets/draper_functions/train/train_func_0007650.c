_CON_ComputeLineHeight( FNT_font_t font , int line )
{
	if ( CON_console.text[ line ][ 0 ] == 0 ) {

		CON_console.heights[ line ] = font->size;
	} else {

		struct FNT_window_s box;
		box.x = 0 , box.y = viddef.height;
		box.width = viddef.width - font->size * 5 , box.height = 0;

		if ( CON_console.lCount[ line ] == 1 ) {
			FNT_WrappedPrint( font , CON_console.text[ line ] , FNT_CMODE_QUAKE_SRS ,
				FNT_ALIGN_LEFT , 0 , &box , FNT_colors[ 0 ] );
		} else {
			char * buffer = Z_Malloc( CON_console.lCount[ line ] * CON_LINE_LENGTH );
			_CON_CopyLine( buffer , line );
			FNT_WrappedPrint( font , buffer , FNT_CMODE_QUAKE_SRS ,
				FNT_ALIGN_LEFT , 0 , &box , FNT_colors[ 0 ] );
			Z_Free( buffer );
		}

		if ( box.height == 0 ) {
			CON_console.heights[ line ] = font->size;
		} else {
			CON_console.heights[ line ] = box.height;
		}
	}
}
