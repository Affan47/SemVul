gst_cogcolorspace_init (GstCogcolorspace * colorspace,
    GstCogcolorspaceClass * klass)
{
  GST_DEBUG ("gst_cogcolorspace_init");

  colorspace->quality = DEFAULT_QUALITY;
}
