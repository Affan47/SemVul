FT_Get_PFR_Advance( FT_Face   face,
                      FT_UInt   gindex,
                      FT_Pos   *aadvance )
  {
    FT_Error               error;
    FT_Service_PfrMetrics  service;


    if ( !face )
      return FT_THROW( Invalid_Face_Handle );

    if ( !aadvance )
      return FT_THROW( Invalid_Argument );

    service = ft_pfr_check( face );
    if ( service )
      error = service->get_advance( face, gindex, aadvance );
    else

      error = FT_THROW( Invalid_Argument );

    return error;
  }
