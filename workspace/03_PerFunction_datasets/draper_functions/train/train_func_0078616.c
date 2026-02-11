RedrawNames( rb )
  BBox  rb;
  {
    Coord  x, y;
    Trptr  t;
    int    i;

    rb.left = max( rb.left, namesBox.left );
    rb.right = min( rb.right, namesBox.right );
    rb.top = max( namesBox.top, rb.top );
    rb.bot = min( namesBox.bot, rb.bot );
    FillBox( window, rb, gcs.white );

    for( i = traces.disp, t = traces.first; i != 0; i--, t = t->next )
	if( rb.top <= t->bot )
	    break;

    x = namesBox.right - 2;
    while( i != 0 and rb.bot >= t->top )
      {
	y = (t->bot + t->top + CHARHEIGHT) / 2;
	StrRight( window, t->name, t->len, x, y, gcs.black );
	if( t == selectedTrace )
	    UnderlineTrace( t, gcs.black );
	i--;
	t = t->next;
      }
  }
