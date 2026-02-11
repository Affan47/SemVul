ft_outline_glyph_transform( FT_Glyph          outline_glyph,
                              const FT_Matrix*  matrix,
                              const FT_Vector*  delta )
  {
    FT_OutlineGlyph  glyph = (FT_OutlineGlyph)outline_glyph;


    if ( matrix )
      FT_Outline_Transform( &glyph->outline, matrix );

    if ( delta )
      FT_Outline_Translate( &glyph->outline, delta->x, delta->y );
  }
