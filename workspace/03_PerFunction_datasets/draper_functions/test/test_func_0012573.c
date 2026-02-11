WidgetActivated( Widget *widget, Window *win ) {
  if ( widget->ID() == 0 )
    Set( static_cast<SliderWidget *>(widget)->Level() );
  return GUI_OK;
}
