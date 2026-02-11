PS_Lookup_Unicode( PS_Unicodes*  table,
                     FT_ULong      unicode )
  {
    PS_UniMap  *min, *max, *mid;


    min = table->maps;
    max = min + table->num_maps - 1;

    while ( min <= max )
    {
      mid = min + ( max - min ) / 2;
      if ( mid->unicode == unicode )
        return mid->glyph_index;

      if ( min == max )
        break;

      if ( mid->unicode < unicode )
        min = mid + 1;
      else
        max = mid - 1;
    }

    return 0xFFFF;
  }
