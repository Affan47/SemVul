gst_oss_sink_prepare (GstAudioSink * asink, GstRingBufferSpec * spec)
{
  GstOssSink *oss;
  struct audio_buf_info info;
  int mode;
  int tmp;

  oss = GST_OSSSINK (asink);


  mode = fcntl (oss->fd, F_GETFL);
  mode &= ~O_NONBLOCK;
  if (fcntl (oss->fd, F_SETFL, mode) == -1) {


    gst_oss_sink_close (asink);
    if ((oss->fd = open (oss->device, O_WRONLY, 0)) == -1)
      goto non_block;
  }

  tmp = gst_oss_sink_get_format (spec->format);
  if (tmp == 0)
    goto wrong_format;

  if (spec->width != 16 && spec->width != 8)
    goto dodgy_width;

  SET_PARAM (oss, SNDCTL_DSP_SETFMT, tmp, "SETFMT");
  if (spec->channels == 2)
    SET_PARAM (oss, SNDCTL_DSP_STEREO, 1, "STEREO");
  SET_PARAM (oss, SNDCTL_DSP_CHANNELS, spec->channels, "CHANNELS");
  SET_PARAM (oss, SNDCTL_DSP_SPEED, spec->rate, "SPEED");

  tmp = ilog2 (spec->segsize);
  tmp = ((spec->segtotal & 0x7fff) << 16) | tmp;
  GST_DEBUG_OBJECT (oss, "set segsize: %d, segtotal: %d, value: %08x",
      spec->segsize, spec->segtotal, tmp);

  SET_PARAM (oss, SNDCTL_DSP_SETFRAGMENT, tmp, "SETFRAGMENT");
  GET_PARAM (oss, SNDCTL_DSP_GETOSPACE, &info, "GETOSPACE");

  spec->segsize = info.fragsize;
  spec->segtotal = info.fragstotal;

  spec->bytes_per_sample = (spec->width / 8) * spec->channels;
  oss->bytes_per_sample = (spec->width / 8) * spec->channels;

  GST_DEBUG_OBJECT (oss, "got segsize: %d, segtotal: %d, value: %08x",
      spec->segsize, spec->segtotal, tmp);

  return TRUE;


non_block:
  {
    GST_ELEMENT_ERROR (oss, RESOURCE, SETTINGS, (NULL),
        ("Unable to set device %s in non blocking mode: %s",
            oss->device, g_strerror (errno)));
    return FALSE;
  }
wrong_format:
  {
    GST_ELEMENT_ERROR (oss, RESOURCE, SETTINGS, (NULL),
        ("Unable to get format %d", spec->format));
    return FALSE;
  }
dodgy_width:
  {
    GST_ELEMENT_ERROR (oss, RESOURCE, SETTINGS, (NULL),
        ("unexpected width %d", spec->width));
    return FALSE;
  }
}
