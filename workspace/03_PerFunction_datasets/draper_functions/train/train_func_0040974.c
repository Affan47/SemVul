null_part_in_key(KEY_PART *key_part, const uchar *key, uint length)
{
  for (const uchar *end=key+length ;
       key < end;
       key+= key_part++->store_length)
  {
    if (key_part->null_bit && *key)
      return 1;
  }
  return 0;
}
