dac_lookup()
{
  if(NULL==dac_itself)
    dac_itself=lookup_widget(sp->im_widget[MAIN_WIN],  "drawingarea_color");
  return dac_itself;
}
