EraseCursor()
  {
    Coord  x, d;
    int w;

    x = TimeToX( tims.cursor );
    FillAREA( window, x, traceBox.top, 1, traceBox.bot - traceBox.top,
     gcs.curs_off );

    if (tims.cursor < TIME_BOUND && tims.delta < TIME_BOUND) {
       d = TimeToX(tims.delta);
       w = (int)(d - x);
       if (w < 0) {
	  x = d;
	  w = -w;
       }
       FillAREA(window, x, traceBox.top, w, traceBox.bot - traceBox.top,
           		gcs.unhilite);
    }
  }
