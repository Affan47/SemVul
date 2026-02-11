test_cubic_extrema( FT_Pos    y1,
                      FT_Pos    y2,
                      FT_Pos    y3,
                      FT_Pos    y4,
                      FT_Fixed  u,
                      FT_Pos*   min,
                      FT_Pos*   max )
  {

    FT_Pos    b = y3 - 2*y2 + y1;
    FT_Pos    c = y2 - y1;
    FT_Pos    d = y1;
    FT_Pos    y;
    FT_Fixed  uu;

    FT_UNUSED ( y4 );


    if ( u > 0 && u < 0x10000L )
    {
      uu = FT_MulFix( u, u );
      y  = d + FT_MulFix( c, 2*u ) + FT_MulFix( b, uu );

      if ( y < *min ) *min = y;
      if ( y > *max ) *max = y;
    }
  }
