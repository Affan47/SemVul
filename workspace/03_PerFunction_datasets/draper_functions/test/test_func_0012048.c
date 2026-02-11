Destroy_AN1_Waypoint(void* vwpt)
{

  an1_waypoint_record* wpt = (an1_waypoint_record*)vwpt;
  xfree(wpt->name);
  xfree(wpt->fontname);
  if (wpt->url) {
    xfree(wpt->url);
  }
  if (wpt->comment) {
    xfree(wpt->comment);
  }
  if (wpt->image_name) {
    xfree(wpt->image_name);
  }
  xfree(vwpt);
}
