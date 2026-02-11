FT_Glyph_Copy( FT_Glyph   source,
                 FT_Glyph  *target )
  {
    FT_Glyph               copy;
    FT_Error               error;
    const FT_Glyph_Class*  clazz;


    if ( !target )
    {
      error = FT_Err_Invalid_Argument;
      goto Exit;
    }

    *target = 0;

    if ( !source || !source->clazz )
    {
      error = FT_Err_Invalid_Argument;
      goto Exit;
    }

    clazz = source->clazz;
    error = ft_new_glyph( source->library, clazz, &copy );
    if ( error )
      goto Exit;

    copy->advance = source->advance;
    copy->format  = source->format;

    if ( clazz->glyph_copy )
      error = clazz->glyph_copy( source, copy );

    if ( error )
      FT_Done_Glyph( copy );
    else
      *target = copy;

  Exit:
    return error;
  }
