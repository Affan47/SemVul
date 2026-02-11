FT_Stroker_GetCounts( FT_Stroker  stroker,
                        FT_UInt    *anum_points,
                        FT_UInt    *anum_contours )
  {
    FT_UInt   count1, count2, num_points   = 0;
    FT_UInt   count3, count4, num_contours = 0;
    FT_Error  error;


    if ( !stroker )
    {
      error = FT_THROW( Invalid_Argument );
      goto Exit;
    }

    error = ft_stroke_border_get_counts( stroker->borders + 0,
                                         &count1, &count2 );
    if ( error )
      goto Exit;

    error = ft_stroke_border_get_counts( stroker->borders + 1,
                                         &count3, &count4 );
    if ( error )
      goto Exit;

    num_points   = count1 + count3;
    num_contours = count2 + count4;

  Exit:
    if ( anum_points )
      *anum_points   = num_points;

    if ( anum_contours )
      *anum_contours = num_contours;

    return error;
  }
