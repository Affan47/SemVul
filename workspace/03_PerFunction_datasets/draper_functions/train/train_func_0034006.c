rsn_parsetter_check_caps (RsnParSetter * parset, GstCaps * caps)
{
  GstStructure *s;
  gint width, height;
  gint par_n, par_d;
  guint dar_n, dar_d;
  gboolean ret = FALSE;

  g_mutex_lock (parset->caps_lock);

  if (caps == parset->in_caps_last ||
      gst_caps_is_equal (caps, parset->in_caps_last)) {
    ret = parset->in_caps_was_ok;
    goto out;
  }


  s = gst_caps_get_structure (caps, 0);
  if (s == NULL)
    goto out;

  if (!gst_structure_get_int (s, "width", &width) ||
      !gst_structure_get_int (s, "height", &height))
    goto out;

  if (!gst_structure_get_fraction (s, "pixel-aspect-ratio", &par_n, &par_d))
    par_n = par_d = 1;

  if (!gst_video_calculate_display_ratio (&dar_n, &dar_d, width, height,
          par_n, par_d, 1, 1))
    goto out;

  GST_DEBUG_OBJECT (parset,
      "Incoming video caps now: w %d h %d PAR %d/%d = DAR %d/%d",
      width, height, par_n, par_d, dar_n, dar_d);

  if (parset->is_widescreen) {
    if (dar_n == 16 && dar_d == 9)
      ret = TRUE;
  } else {
    if (dar_n == 4 && dar_d == 3)
      ret = TRUE;
  }

  gst_caps_replace (&parset->in_caps_last, caps);
  gst_caps_replace (&parset->in_caps_converted, NULL);
  parset->in_caps_was_ok = ret;

out:
  g_mutex_unlock (parset->caps_lock);
  return ret;
}
