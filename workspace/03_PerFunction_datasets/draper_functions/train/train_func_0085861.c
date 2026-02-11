get_bg_color(GLParser & parser)
{
  unsigned long retval=default_bg_color;
  DEBUG_MSG("DjVuANT::get_bg_color(): getting background color ...\n");
  DEBUG_MAKE_INDENT(3);
  G_TRY
  {
    GP<GLObject> obj=parser.get_object(BACKGROUND_TAG);
    if (obj && obj->get_list().size()==1)
    {
      GUTF8String color=(*obj)[0]->get_symbol();
      DEBUG_MSG("color='" << color << "'\n");
      retval=cvt_color(color, 0xffffff);
    }
#ifndef NDEBUG
    if(retval == default_bg_color)
    {
      DEBUG_MSG("can't find any.\n");
    }
#endif
  } G_CATCH_ALL {} G_ENDCATCH;
#ifndef NDEBUG
  if(retval == default_bg_color)
  {
    DEBUG_MSG("resetting color to 0xffffffff (UNSPEC)\n");
  }
#endif
  return retval;
}
