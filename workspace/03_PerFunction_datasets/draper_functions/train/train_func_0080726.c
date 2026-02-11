get_strinfo (int idx)
{
  if (VEC_length (strinfo, stridx_to_strinfo) <= (unsigned int) idx)
    return NULL;
  return VEC_index (strinfo, stridx_to_strinfo, idx);
}
