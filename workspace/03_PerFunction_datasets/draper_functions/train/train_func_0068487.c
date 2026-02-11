ges_track_audio_transition_create_element (GESTrackObject * object)
{
  GESTrackAudioTransition *self;
  GstElement *topbin, *iconva, *iconvb, *oconv;
  GObject *atarget, *btarget = NULL;
  const gchar *propname = "volume";
  GstElement *mixer = NULL;
  GstPad *sinka_target, *sinkb_target, *src_target, *sinka, *sinkb, *src;
  GstController *acontroller, *bcontroller;
  GstInterpolationControlSource *acontrol_source, *bcontrol_source;

  self = GES_TRACK_AUDIO_TRANSITION (object);


  GST_LOG ("creating an audio bin");

  topbin = gst_bin_new ("transition-bin");
  iconva = gst_element_factory_make ("audioconvert", "tr-aconv-a");
  iconvb = gst_element_factory_make ("audioconvert", "tr-aconv-b");
  oconv = gst_element_factory_make ("audioconvert", "tr-aconv-output");

  gst_bin_add_many (GST_BIN (topbin), iconva, iconvb, oconv, NULL);

  mixer = gst_element_factory_make ("adder", NULL);
  gst_bin_add (GST_BIN (topbin), mixer);

  atarget = link_element_to_mixer_with_volume (GST_BIN (topbin), iconva, mixer);
  btarget = link_element_to_mixer_with_volume (GST_BIN (topbin), iconvb, mixer);

  g_assert (atarget && btarget);

  fast_element_link (mixer, oconv);

  sinka_target = gst_element_get_static_pad (iconva, "sink");
  sinkb_target = gst_element_get_static_pad (iconvb, "sink");
  src_target = gst_element_get_static_pad (oconv, "src");

  sinka = gst_ghost_pad_new ("sinka", sinka_target);
  sinkb = gst_ghost_pad_new ("sinkb", sinkb_target);
  src = gst_ghost_pad_new ("src", src_target);

  gst_element_add_pad (topbin, src);
  gst_element_add_pad (topbin, sinka);
  gst_element_add_pad (topbin, sinkb);


  gst_object_unref (sinka_target);
  gst_object_unref (sinkb_target);
  gst_object_unref (src_target);


  acontroller = gst_object_control_properties (atarget, propname, NULL);
  bcontroller = gst_object_control_properties (btarget, propname, NULL);

  g_assert (acontroller && bcontroller);

  acontrol_source = gst_interpolation_control_source_new ();
  gst_controller_set_control_source (acontroller,
      propname, GST_CONTROL_SOURCE (acontrol_source));
  gst_interpolation_control_source_set_interpolation_mode (acontrol_source,
      GST_INTERPOLATE_LINEAR);

  bcontrol_source = gst_interpolation_control_source_new ();
  gst_controller_set_control_source (bcontroller,
      propname, GST_CONTROL_SOURCE (bcontrol_source));
  gst_interpolation_control_source_set_interpolation_mode (bcontrol_source,
      GST_INTERPOLATE_LINEAR);

  self->priv->a_controller = acontroller;
  self->priv->b_controller = bcontroller;
  self->priv->a_control_source = acontrol_source;
  self->priv->b_control_source = bcontrol_source;

  return topbin;
}
