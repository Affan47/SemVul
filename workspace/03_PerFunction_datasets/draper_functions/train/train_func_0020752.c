merge_object_sizes (struct object_size_info *osi, tree dest, tree orig,
		    unsigned HOST_WIDE_INT offset)
{
  int object_size_type = osi->object_size_type;
  unsigned int varno = SSA_NAME_VERSION (dest);
  unsigned HOST_WIDE_INT orig_bytes;

  if (object_sizes[object_size_type][varno] == unknown[object_size_type])
    return false;
  if (offset >= offset_limit)
    {
      object_sizes[object_size_type][varno] = unknown[object_size_type];
      return false;
    }

  if (osi->pass == 0)
    collect_object_sizes_for (osi, orig);

  orig_bytes = object_sizes[object_size_type][SSA_NAME_VERSION (orig)];
  if (orig_bytes != unknown[object_size_type])
    orig_bytes = (offset > orig_bytes)
		 ? (unsigned HOST_WIDE_INT) 0 : orig_bytes - offset;

  if ((object_size_type & 2) == 0)
    {
      if (object_sizes[object_size_type][varno] < orig_bytes)
	{
	  object_sizes[object_size_type][varno] = orig_bytes;
	  osi->changed = true;
	}
    }
  else
    {
      if (object_sizes[object_size_type][varno] > orig_bytes)
	{
	  object_sizes[object_size_type][varno] = orig_bytes;
	  osi->changed = true;
	}
    }
  return bitmap_bit_p (osi->reexamine, SSA_NAME_VERSION (orig));
}
