gst_audio_panorama_transform_m2s_float (GstAudioPanorama * filter,
    gfloat * idata, gfloat * odata, guint num_samples)
{
  guint i;
  gfloat val;
  gdouble rpan, lpan;


  rpan = (gdouble) (filter->panorama + 1.0) / 2.0;
  lpan = 1.0 - rpan;

  for (i = 0; i < num_samples; i++) {
    val = *idata++;

    *odata++ = val * lpan;
    *odata++ = val * rpan;
  }
}
