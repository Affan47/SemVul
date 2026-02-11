ft_new_glyph( FT_Library             library,
                 const FT_Glyph_Class*  clazz,
                 FT_Glyph*              aglyph )
   {
     FT_Memory  memory = library->memory;
     FT_Error   error;
     FT_Glyph   glyph;


     *aglyph = 0;

     if ( !ALLOC( glyph, clazz->glyph_size ) )
     {
       glyph->library = library;
       glyph->clazz   = clazz;
       glyph->format  = clazz->glyph_format;

       *aglyph = glyph;
     }

     return error;
   }
