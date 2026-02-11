gst_handdetect_finalize (GObject * obj)
{
  GstHanddetect *filter = GST_HANDDETECT (obj);

  if (filter->cvImage)
    cvReleaseImage (&filter->cvImage);
  if (filter->cvGray)
    cvReleaseImage (&filter->cvGray);
  g_free (filter->profile_fist);
  g_free (filter->profile_palm);

  G_OBJECT_CLASS (gst_handdetect_parent_class)->finalize (obj);
}
