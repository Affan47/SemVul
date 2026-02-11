evas_common_font_memory_hinting_load(const char *source, const char *name, int size, const void *data, int data_size, Font_Hint_Flags hinting, Font_Rend_Flags wanted_rend)
{
   RGBA_Font *fn;

   fn = evas_common_font_memory_load(source, name, size, data, data_size, wanted_rend);
   if (fn) evas_common_font_hinting_set(fn, hinting);
   return fn;
}
