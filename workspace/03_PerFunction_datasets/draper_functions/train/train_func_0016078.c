eng_output_redraws_rect_add(void *data, int x, int y, int w, int h)
{
   Render_Engine *re = NULL;

   if (!(re = (Render_Engine *)data)) return;
   if (re->tb) evas_common_tilebuf_add_redraw(re->tb, x, y, w, h);
}
