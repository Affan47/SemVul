debug_output( char c )
{
	if ( c == '\t' ) {
		int next_tab = ((debug_x/28)+1)*28;

		if ( next_tab >= DCOLS-1 ) {
			debug_x=0;
			debug_y++;
			scroll_times++;
			if ( debug_y >= DROWS ) {
				int i;
				for (i=1; i<DROWS; i++ ) {
					strcpy_s( debug_text[i-1], debug_text[i] );
				}
				debug_y = DROWS-1;
				debug_x = 0;
				debug_text[debug_y][debug_x] = 0;
			}
			debug_text[debug_y][debug_x] = 0;
			return;
		}

		for ( ; debug_x < next_tab; ) {
			debug_text[debug_y][debug_x++] = ' ';
		}
		debug_text[debug_y][debug_x] = 0;
		return;
	}

	if ( (c == '\n') || (debug_x >= DCOLS-1) ) {
		debug_x=0;
		debug_y++;
		scroll_times++;
		if ( debug_y >= DROWS ) {
			int i;
			for (i=1; i<DROWS; i++ ) {
				strcpy_s( debug_text[i-1], debug_text[i] );
			}
			debug_y = DROWS-1;
			debug_x = 0;
			debug_text[debug_y][debug_x] = 0;
		}
		debug_text[debug_y][debug_x] = 0;
		if ( c == '\n' ) {
			return;
		}
	}

	debug_text[debug_y][debug_x++] = c;
	debug_text[debug_y][debug_x] = 0;
}
