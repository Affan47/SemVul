ft_gzip_check_header( FT_Stream  stream )
  {
    FT_Error  error;
    FT_Byte   head[4];


    if ( FT_STREAM_SEEK( 0 )       ||
         FT_STREAM_READ( head, 4 ) )
      goto Exit;


    if ( head[0] != 0x1F              ||
         head[1] != 0x8B              ||
         head[2] != Z_DEFLATED        ||
        (head[3] & FT_GZIP_RESERVED)  )
    {
      error = FT_THROW( Invalid_File_Format );
      goto Exit;
    }


    (void)FT_STREAM_SKIP( 6 );


    if ( head[3] & FT_GZIP_EXTRA_FIELD )
    {
      FT_UInt  len;


      if ( FT_READ_USHORT_LE( len ) ||
           FT_STREAM_SKIP( len )    )
        goto Exit;
    }


    if ( head[3] & FT_GZIP_ORIG_NAME )
      for (;;)
      {
        FT_UInt  c;


        if ( FT_READ_BYTE( c ) )
          goto Exit;

        if ( c == 0 )
          break;
      }


    if ( head[3] & FT_GZIP_COMMENT )
      for (;;)
      {
        FT_UInt  c;


        if ( FT_READ_BYTE( c ) )
          goto Exit;

        if ( c == 0 )
          break;
      }


    if ( head[3] & FT_GZIP_HEAD_CRC )
      if ( FT_STREAM_SKIP( 2 ) )
        goto Exit;

  Exit:
    return error;
  }
