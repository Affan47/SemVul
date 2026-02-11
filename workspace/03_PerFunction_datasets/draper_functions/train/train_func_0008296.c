get_paramtags(void) const
{
  GUTF8String retval;
  if(zoom > 0)
  {
    retval+="<PARAM name=\"" ZOOM_TAG "\" value=\""+GUTF8String(zoom)+="\" />\n";
  }else if(zoom && ((-zoom)<zoom_strings_size))
  {
    retval+="<PARAM name=\"" ZOOM_TAG "\" value=\""+GUTF8String(zoom_strings[-zoom])+"\" />\n";
  }
  if((mode>0)&&(mode<mode_strings_size))
  {
    retval+="<PARAM name=\"" MODE_TAG "\" value=\""+GUTF8String(mode_strings[mode])+"\" />\n";
  }
  if((hor_align>ALIGN_UNSPEC)&&(hor_align<align_strings_size))
  {
    retval+="<PARAM name=\"" HALIGN_TAG "\" value=\""+GUTF8String(align_strings[hor_align])+"\" />\n";
  }
  if((ver_align>ALIGN_UNSPEC)&&(ver_align<align_strings_size))
  {
    retval+="<PARAM name=\"" VALIGN_TAG "\" value=\""+GUTF8String(align_strings[ver_align])+"\" />\n";
  }
  if((bg_color&0xffffff) == bg_color)
  {
    retval+="<PARAM name=\"" BACKGROUND_TAG "\" value=\""+GUTF8String().format("#%06lX",bg_color)+"\" />\n";
  }
  return retval;
}
