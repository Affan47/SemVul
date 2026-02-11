refmpn_copy (mp_ptr rp, mp_srcptr sp, mp_size_t size)
{
  ASSERT (refmpn_overlap_fullonly_p (rp, sp, size));
  refmpn_copyi (rp, sp, size);
}
