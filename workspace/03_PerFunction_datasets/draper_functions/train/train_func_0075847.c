set_strinfo (int idx, strinfo si)
{
  if (vec_safe_length (stridx_to_strinfo) && (*stridx_to_strinfo)[0])
    unshare_strinfo_vec ();
  if (vec_safe_length (stridx_to_strinfo) <= (unsigned int) idx)
    vec_safe_grow_cleared (stridx_to_strinfo, idx + 1);
  (*stridx_to_strinfo)[idx] = si;
}
