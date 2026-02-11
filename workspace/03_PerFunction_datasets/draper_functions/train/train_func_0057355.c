df_grow_ref_info (struct df_ref_info *ref_info, unsigned int new_size)
{
  if (ref_info->refs_size < new_size)
    {
      ref_info->refs = XRESIZEVEC (df_ref, ref_info->refs, new_size);
      memset (ref_info->refs + ref_info->refs_size, 0,
	      (new_size - ref_info->refs_size) *sizeof (df_ref));
      ref_info->refs_size = new_size;
    }
}
