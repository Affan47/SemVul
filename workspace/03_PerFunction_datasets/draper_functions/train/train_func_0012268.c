evas_common_font_ascent_descent_get(RGBA_Font *fn, const Evas_Text_Props *text_props, int *ascent, int *descent)
{
   int asc = 0, desc = 0;
   int max_asc, max_desc;

   max_asc = evas_common_font_ascent_get(fn);
   max_desc = evas_common_font_descent_get(fn);


   desc = max_desc;

   EVAS_FONT_WALK_TEXT_INIT();
   EVAS_FONT_WALK_TEXT_START()
     {
        EVAS_FONT_WALK_TEXT_WORK();
        if (!EVAS_FONT_WALK_IS_VISIBLE) continue;

        if ((EVAS_FONT_WALK_PEN_Y + EVAS_FONT_WALK_Y_OFF + EVAS_FONT_WALK_Y_BEAR) > asc)
          {
             asc = EVAS_FONT_WALK_PEN_Y + EVAS_FONT_WALK_Y_OFF + EVAS_FONT_WALK_Y_BEAR;
          }
     }
   EVAS_FONT_WALK_TEXT_END();

   if (ascent) *ascent = (asc > max_asc) ? asc : max_asc;
   if (descent) *descent = (desc < max_desc) ? desc : max_desc;
}
