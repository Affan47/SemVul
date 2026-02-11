matsushita_copy_raw_to_frontend (Matsushita_Scanner * dev, SANE_Byte * buf,
				 size_t * len)
{
  size_t size;

  size = dev->image_end - dev->image_begin;
  if (size > *len)
    {
      size = *len;
    }
  *len = size;

  memcpy (buf, dev->image + dev->image_begin, size);
  dev->image_begin += size;
}
