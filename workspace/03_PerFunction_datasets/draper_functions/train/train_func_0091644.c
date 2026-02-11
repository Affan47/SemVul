DrawMenu( m )
  Menu  *m;
  {
    MenuItem  *item;
    char      *s;
    int       len;

    for( item = m->items; item->str != NULL; item++ )
      {
	s = item->str;
	len = item->len;
	if (item->mark == MENU_MARK)
	  {
	    XCopyArea( display, pix.chk, m->w, gcs.black, 0, 0, 6, 8, 1,
	     (item->top + item->bot - 8)/2 );
	  }

	 StrCenter( m->w, s, len, 0, m->width - 1, item->bot - 1, gcs.black );
      }
  }
