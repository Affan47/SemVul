mag_start_track(int i, GdkEventButton  *event)
{
  if(!mag_area) return FALSE;
  mag_xy_track(i,event->x,event->y);
  return TRUE;
}
