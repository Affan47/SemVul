SetColors()
  {
    XColor    coldef[ MAX_NCOLORS ];

    if( PlanesOfScreen( screen ) < 2 )
	goto mono;

    if( not GetColor( DEFL_BG, coldef, BACKGROUND_COLOR ) )
	goto mono;
    colors.black = coldef[ BACKGROUND_COLOR ].pixel;

    if( not GetColor( DEFL_FG, coldef, FOREGROUND_COLOR ) )
	goto mono;
    colors.white = coldef[ FOREGROUND_COLOR ].pixel;

    if( GetColor( DEFL_TRCOLOR, coldef, TRACE_COLOR ) )
	colors.traces = coldef[ TRACE_COLOR ].pixel;
    else
	colors.traces = colors.white;

    if( GetColor( DEFL_HIGL, coldef, HIGHLIGHT_COLOR ) )
      {
	colors.color_hilite = TRUE;
	colors.hilite = coldef[ HIGHLIGHT_COLOR ].pixel;
	if( ((colors.black | colors.hilite) == colors.hilite and
	 (colors.traces & ~colors.hilite) == colors.traces ) )
	    colors.disj = 1;
	else if( (colors.black & ~colors.hilite) == colors.hilite and
	 (colors.traces | colors.hilite) == colors.traces )
	    colors.disj = 2;
	else
	    colors.disj = 0;
      }
    else
      {
	colors.disj = 0;
	colors.hilite = colors.black;
	colors.color_hilite = FALSE;
	colors.mono = TRUE;
      }

    if( GetColor( DEFL_BANN_BG, coldef, BANNER_BG_COLOR ) )
	colors.banner_bg = coldef[ BANNER_BG_COLOR ].pixel;
    else
	colors.banner_bg = colors.white;

    if( GetColor( DEFL_BANN_FG, coldef, BANNER_FG_COLOR ) )
	colors.banner_fg = coldef[ BANNER_FG_COLOR ].pixel;
    else
	colors.banner_fg = colors.black;

    if( GetColor( DEFL_BDRCOLOR, coldef, BORDER_COLOR ) )
	colors.border = coldef[ BORDER_COLOR ].pixel;
    else
	colors.border = colors.black;

    return;

  mono:
    colors.mono = TRUE;
    colors.color_hilite = FALSE;
    colors.disj = 0;
    colors.black = BlackPixelOfScreen( screen );
    colors.white = WhitePixelOfScreen( screen );
    if( strcmp( GetXDefault( DEFL_RV ), "on" ) == 0 )
	SWAP( Pixel, colors.black, colors.white );
    colors.traces = colors.banner_bg = colors.white;
    colors.hilite = colors.banner_fg = colors.border = colors.black;
  }
