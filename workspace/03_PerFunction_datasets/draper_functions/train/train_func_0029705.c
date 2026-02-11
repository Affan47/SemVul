gst_oss4_mixer_watch_process_changes (GstOss4Mixer * mixer)
{
  GList *c, *t, *tracks = NULL;

  GST_INFO_OBJECT (mixer, "mixer interface or control changed");


  for (c = g_list_last (mixer->controls); c != NULL; c = c->prev) {
    GstOss4MixerControl *mc = c->data;
    oss_mixer_value ossval = { 0, };

    mc->changed = FALSE;
    mc->list_changed = FALSE;


    if (!mc->used)
      continue;


    if (mc->mixext.type == MIXT_DEVROOT || mc->mixext.type == MIXT_GROUP)
      continue;


    if (mc->mixext.type == MIXT_ENUM && mc->enum_version != 0) {
      if (gst_oss4_mixer_enum_control_update_enum_list (mixer, mc))
        mc->list_changed = TRUE;
    }

    ossval.dev = mc->mixext.dev;
    ossval.ctrl = mc->mixext.ctrl;
    ossval.timestamp = mc->mixext.timestamp;

    if (ioctl (mixer->fd, SNDCTL_MIX_READ, &ossval) == -1) {
      if (errno == EIDRM || errno == EFAULT) {
        GST_DEBUG ("%s has disappeared", mc->mixext.extname);
        goto mixer_changed;
      }
      GST_WARNING_OBJECT (mixer, "MIX_READ failed: %s", g_strerror (errno));

      continue;
    }

    if (ossval.value == mc->last_val) {

      continue;
    }

    mc->last_val = ossval.value;
    GST_LOG_OBJECT (mixer, "%s changed value to %u 0x%08x",
        mc->mixext.extname, ossval.value, ossval.value);
    mc->changed = TRUE;
  }


  tracks = g_list_copy (mixer->tracks);
  g_list_foreach (tracks, (GFunc) g_object_ref, NULL);

  GST_OBJECT_UNLOCK (mixer);


  for (t = tracks; t != NULL; t = t->next) {
    GstMixerTrack *track = t->data;

    if (GST_IS_OSS4_MIXER_SLIDER (track)) {
      gst_oss4_mixer_slider_process_change_unlocked (track);
    } else if (GST_IS_OSS4_MIXER_SWITCH (track)) {
      gst_oss4_mixer_switch_process_change_unlocked (track);
    } else if (GST_IS_OSS4_MIXER_ENUM (track)) {
      gst_oss4_mixer_enum_process_change_unlocked (track);
    }

    g_object_unref (track);
  }
  g_list_free (tracks);

  GST_OBJECT_LOCK (mixer);
  return;

mixer_changed:
  {
    GST_OBJECT_UNLOCK (mixer);
    gst_mixer_mixer_changed (GST_MIXER (mixer));
    GST_OBJECT_LOCK (mixer);
    return;
  }
}
