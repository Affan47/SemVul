rsrc_count_entries (bfd *          abfd,
		    bfd_boolean    is_name,
		    bfd_byte *     datastart,
		    bfd_byte *     data,
		    bfd_byte *     dataend,
		    bfd_vma        rva_bias)
{
  unsigned long entry, addr, size;

  if (data + 8 >= dataend)
    return dataend + 1;

  if (is_name)
    {
      bfd_byte * name;

      entry = (long) bfd_get_32 (abfd, data);

      if (HighBitSet (entry))
	name = datastart + WithoutHighBit (entry);
      else
	name = datastart + entry - rva_bias;

      if (name + 2 >= dataend)
	return dataend + 1;

      unsigned int len = bfd_get_16 (abfd, name);
      if (len == 0 || len > 256)
	return dataend + 1;

      sizeof_strings += (len + 1) * 2;
    }

  entry = (long) bfd_get_32 (abfd, data + 4);

  if (HighBitSet (entry))
    return rsrc_count_directory (abfd,
				 datastart,
				 datastart + WithoutHighBit (entry),
				 dataend, rva_bias);

  if (datastart + entry + 16 >= dataend)
    return dataend + 1;

  addr = (long) bfd_get_32 (abfd, datastart + entry);
  size = (long) bfd_get_32 (abfd, datastart + entry + 4);

  sizeof_leaves += 16;

  return datastart + addr - rva_bias + size;
}
