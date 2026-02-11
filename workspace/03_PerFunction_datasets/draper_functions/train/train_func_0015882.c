gst_control_point_find (gconstpointer p1, gconstpointer p2, gpointer user_data)
{
  GstClockTime ct1 = ((GstControlPoint *) p1)->timestamp;
  GstClockTime ct2 = *(GstClockTime *) p2;

  return ((ct1 < ct2) ? -1 : ((ct1 == ct2) ? 0 : 1));
}
