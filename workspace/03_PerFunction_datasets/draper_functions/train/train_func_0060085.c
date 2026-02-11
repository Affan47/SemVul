rewrite_reflection_indexes (void *arg)
{
  bitmap_iterator bi;
  unsigned int offset;
  vec<int> *map = (vec<int> *) arg;
  unsigned char *data = TYPE_REFLECTION_DATA (current_class);

  if (map)
    {
      EXECUTE_IF_SET_IN_BITMAP (field_offsets, 0, offset, bi)
	{
	  uint16 index = annotation_read_short (data + offset);
	  annotation_rewrite_short
	    ((*map)[index], data + offset);
	}
    }
}
