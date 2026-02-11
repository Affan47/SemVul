ft_gzip_file_skip_output( FT_GZipFile  zip,
                            FT_ULong     count )
  {
    FT_Error  error = FT_Err_Ok;
    FT_ULong  delta;


    for (;;)
    {
      delta = (FT_ULong)( zip->limit - zip->cursor );
      if ( delta >= count )
        delta = count;

      zip->cursor += delta;
      zip->pos    += delta;

      count -= delta;
      if ( count == 0 )
        break;

      error = ft_gzip_file_fill_output( zip );
      if ( error )
        break;
    }

    return error;
  }
