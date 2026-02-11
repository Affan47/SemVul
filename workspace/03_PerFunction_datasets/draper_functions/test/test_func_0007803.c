DoScrollBar( ev )
  XButtonEvent  *ev;
  {
    TimeType  oldStart, oldSteps;

    if( (ev->x < scrollBox.left) or (ev->x > scrollBox.right) )
	return;

    if( ev->x < scrollBox.left + (ARROW_WIDTH / 2 - 1) )
	MoveLeft( 2 );
    else if( ev->x < traceBox.left )
	MoveLeft( 1 );
    else if( ev->x <= traceBox.right )
      {
	oldStart = tims.start;
	oldSteps = tims.steps;

	switch( ev->button & (Button1 | Button2 | Button3) )
	  {
	    case Button1 :
		StretchLeft( ev->x );
		break;
	    case Button2 :
		MoveBar( ev->x );
		break;
	    case Button3 :
		StretchRight( ev->x );
		break;
	  }
	UpdateScrollBar();
	if( (oldStart != tims.start) or (oldSteps != tims.steps) )
	  {
	    DrawTraces( tims.start, tims.end );
	    RedrawTimes();
	  }
      }
    else if( ev->x < scrollBox.right - (ARROW_WIDTH / 2 - 1) )
      {
	MoveRight( 1 );
      }
    else
	MoveRight( 2 );
  }
