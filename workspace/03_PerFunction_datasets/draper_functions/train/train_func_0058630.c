gst_handdetect_set_caps (GstOpencvVideoFilter * transform,
    gint in_width, gint in_height, gint in_depth, gint in_channels,
    gint out_width, gint out_height, gint out_depth, gint out_channels)
{
  GstHanddetect *filter;
  filter = GST_HANDDETECT (transform);

  if (filter->cvGray)
    cvReleaseImage (&filter->cvGray);
  filter->cvGray =
      cvCreateImage (cvSize (in_width, in_height), IPL_DEPTH_8U, 1);
  if (filter->cvImage)
    cvReleaseImage (&filter->cvImage);
  filter->cvImage =
      cvCreateImage (cvSize (in_width, in_height), IPL_DEPTH_8U, 3);

  if (!filter->cvStorage)
    filter->cvStorage = cvCreateMemStorage (0);
  else
    cvClearMemStorage (filter->cvStorage);
  if (!filter->cvStorage_palm)
    filter->cvStorage_palm = cvCreateMemStorage (0);
  else
    cvClearMemStorage (filter->cvStorage_palm);
  return TRUE;
}
