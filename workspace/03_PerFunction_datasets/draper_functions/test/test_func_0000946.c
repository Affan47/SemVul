combine_strings (strings)
     varray_type strings;
{
  const int wchar_bytes = TYPE_PRECISION (wchar_type_node) / BITS_PER_UNIT;
  const int nstrings = VARRAY_ACTIVE_SIZE (strings);
  tree value, t;
  int length = 1;
  int wide_length = 0;
  int wide_flag = 0;
  int i;
  char *p, *q;


  for (i = 0; i < nstrings; ++i)
    {
      t = VARRAY_TREE (strings, i);

      if (TREE_TYPE (t) == wchar_array_type_node)
	{
	  wide_length += TREE_STRING_LENGTH (t) - wchar_bytes;
	  wide_flag = 1;
	}
      else
	{
	  length += (TREE_STRING_LENGTH (t) - 1);
	  if (C_ARTIFICIAL_STRING_P (t) && !in_system_header)
	    warning ("concatenation of string literals with __FUNCTION__ is deprecated");
	}
    }


  if (wide_flag)
    length = length * wchar_bytes + wide_length;

  p = xmalloc (length);


  q = p;
  for (i = 0; i < nstrings; ++i)
    {
      int len, this_wide;

      t = VARRAY_TREE (strings, i);
      this_wide = TREE_TYPE (t) == wchar_array_type_node;
      len = TREE_STRING_LENGTH (t) - (this_wide ? wchar_bytes : 1);
      if (this_wide == wide_flag)
	{
	  memcpy (q, TREE_STRING_POINTER (t), len);
	  q += len;
	}
      else
	{
	  const int nzeros = (TYPE_PRECISION (wchar_type_node)
			      / BITS_PER_UNIT) - 1;
	  int j, k;

	  if (BYTES_BIG_ENDIAN)
	    {
	      for (k = 0; k < len; k++)
		{
		  for (j = 0; j < nzeros; j++)
		    *q++ = 0;
		  *q++ = TREE_STRING_POINTER (t)[k];
		}
	    }
	  else
	    {
	      for (k = 0; k < len; k++)
		{
		  *q++ = TREE_STRING_POINTER (t)[k];
		  for (j = 0; j < nzeros; j++)
		    *q++ = 0;
		}
	    }
	}
    }


  if (wide_flag)
    {
      for (i = 0; i < wchar_bytes; i++)
	*q++ = 0;
    }
  else
    *q = 0;

  value = build_string (length, p);
  free (p);

  if (wide_flag)
    TREE_TYPE (value) = wchar_array_type_node;
  else
    TREE_TYPE (value) = char_array_type_node;

  return value;
}
