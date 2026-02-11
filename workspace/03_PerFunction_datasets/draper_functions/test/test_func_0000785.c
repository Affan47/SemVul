refmpn_copyi (mp_ptr rp, mp_srcptr sp, mp_size_t size)
{
  mp_size_t i;

  ASSERT (refmpn_overlap_low_to_high_p (rp, sp, size));
  ASSERT (size >= 0);

  for (i = 0; i < size; i++)
    rp[i] = sp[i];
}
