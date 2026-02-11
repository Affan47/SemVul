stp_curve_cache_copy(stp_cached_curve_t *dest, const stp_cached_curve_t *src)
{
  stp_curve_cache_curve_invalidate(dest);
  if (dest != src)
    {
      if (src->curve)
	stp_curve_cache_set_curve_copy(dest, src->curve);
    }
}
