focusblur_diffusion_model_gaussian (FblurDiffusionTable *diffusion,
                                    gfloat               radius,
                                    gfloat               difference)
{
  static gfloat cache_radius = 0.0f;
  static gfloat cache_vr = 0.0f;

  gfloat distribution;
  gfloat vr;

  if (difference - radius >= 1.0f)
    return 0.0f;

  if (radius == cache_radius)
    {
      vr = cache_vr;
    }
  else
    {
      vr = FBLUR_GAUSSIAN_FACTOR * (radius + 1);
      vr = -1.0f / (2.0f * vr * vr);

      cache_radius = radius;
      cache_vr = vr;
    }

  distribution = expf (difference * difference * vr);

  return distribution;
}
