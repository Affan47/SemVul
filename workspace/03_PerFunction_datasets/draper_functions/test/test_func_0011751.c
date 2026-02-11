adjustPointer(void)
{
  if (style()==MSScrollBar::Openlook)
   {
     if (changeType()==Dec)
      {
	XWarpPointer(display(),None,_elevator->window(),0,0,0,0,
		     DefaultElevatorBoxWidth>>1,_elevator->height()>>1);
      }
     else if (changeType()==Inc)
      {
	XWarpPointer(display(),None,_elevator->window(),0,0,0,0,
		     _elevator->width()-(DefaultElevatorBoxWidth>>1),
		     _elevator->height()>>1);
      }
   }
}
