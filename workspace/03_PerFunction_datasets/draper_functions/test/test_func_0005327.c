_fash_glyph_free(Fash_Glyph_Map *fmap)
{
   int i;

   for (i = 0; i <= 0xff; i++)
     {
        RGBA_Font_Glyph *fg = fmap->item[i];
        if ((fg) && (fg != (void *)(-1)))
          {
             FT_Done_Glyph(fg->glyph);

             if (fg->ext_dat_free) fg->ext_dat_free(fg->ext_dat);
             if (fg->glyph_out_free) fg->glyph_out_free(fg->glyph_out);
             free(fg);
             fmap->item[i] = NULL;
          }
     }
  free(fmap);
}
