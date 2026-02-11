ft_conic_is_small_enough( FT_Vector*  base,
                            FT_Angle   *angle_in,
                            FT_Angle   *angle_out )
  {
    FT_Vector  d1, d2;
    FT_Angle   theta;
    FT_Int     close1, close2;


    d1.x = base[1].x - base[2].x;
    d1.y = base[1].y - base[2].y;
    d2.x = base[0].x - base[1].x;
    d2.y = base[0].y - base[1].y;

    close1 = FT_IS_SMALL( d1.x ) && FT_IS_SMALL( d1.y );
    close2 = FT_IS_SMALL( d2.x ) && FT_IS_SMALL( d2.y );

    if ( close1 )
    {
      if ( close2 )
      {


      }
      else
      {
        *angle_in  =
        *angle_out = FT_Atan2( d2.x, d2.y );
      }
    }
    else
    {
      if ( close2 )
      {
        *angle_in  =
        *angle_out = FT_Atan2( d1.x, d1.y );
      }
      else
      {
        *angle_in  = FT_Atan2( d1.x, d1.y );
        *angle_out = FT_Atan2( d2.x, d2.y );
      }
    }

    theta = ft_pos_abs( FT_Angle_Diff( *angle_in, *angle_out ) );

    return FT_BOOL( theta < FT_SMALL_CONIC_THRESHOLD );
  }
