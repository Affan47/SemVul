PS_Build_Unicode_Table( FT_Memory     memory,
                          FT_UInt       num_glyphs,
                          const char**  glyph_names,
                          PS_Unicodes*  table )
  {
    FT_Error  error;


    table->num_maps = 0;
    table->maps     = 0;

    if ( !ALLOC_ARRAY( table->maps, num_glyphs, PS_UniMap ) )
    {
      FT_UInt     n;
      FT_UInt     count;
      PS_UniMap*  map;
      FT_ULong    uni_char;


      map = table->maps;

      for ( n = 0; n < num_glyphs; n++ )
      {
        const char*  gname = glyph_names[n];


        if ( gname )
        {
          uni_char = PS_Unicode_Value( gname );

          if ( uni_char != 0 && uni_char != 0xFFFF )
          {
            map->unicode     = uni_char;
            map->glyph_index = n;
            map++;
          }
        }
      }


      count = (FT_UInt)( map - table->maps );

      if ( count > 0 && REALLOC( table->maps,
                                 num_glyphs * sizeof ( PS_UniMap ),
                                 count * sizeof ( PS_UniMap ) ) )
        count = 0;

      if ( count == 0 )
      {
        FREE( table->maps );
        if ( !error )
          error = PSnames_Err_Invalid_Argument;
      }
      else

        qsort( table->maps, count, sizeof ( PS_UniMap ), compare_uni_maps );

      table->num_maps = count;
    }

    return error;
  }
