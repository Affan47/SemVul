XGetWidgetInfo(const char *text,MagickXWidgetInfo *widget_info)
{


  widget_info->id=(~0);
  widget_info->bevel_width=3;
  widget_info->width=1;
  widget_info->height=1;
  widget_info->x=0;
  widget_info->y=0;
  widget_info->min_y=0;
  widget_info->max_y=0;
  widget_info->raised=True;
  widget_info->active=False;
  widget_info->center=True;
  widget_info->trough=False;
  widget_info->highlight=False;
  widget_info->text=(char *) text;
  widget_info->cursor=(char *) text;
  if (text != (char *) NULL)
    widget_info->cursor+=Extent(text);
  widget_info->marker=(char *) text;
}
