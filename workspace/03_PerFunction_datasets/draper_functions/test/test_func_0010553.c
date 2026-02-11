gst_audio_panorama_transform_s2s_float_simple (GstAudioPanorama * filter,
    gfloat * idata, gfloat * odata, guint num_samples)
{
  guint i;
  gfloat lival, rival, pan;

  if (filter->panorama > 0.0) {
    pan = 1.0 - filter->panorama;
    for (i = 0; i < num_samples; i++) {
      lival = *idata++;
      rival = *idata++;

      *odata++ = lival * pan;
      *odata++ = rival;
    }
  } else {
    pan = 1.0 + filter->panorama;
    for (i = 0; i < num_samples; i++) {
      lival = *idata++;
      rival = *idata++;

      *odata++ = lival;
      *odata++ = rival * pan;
    }
  }
}
