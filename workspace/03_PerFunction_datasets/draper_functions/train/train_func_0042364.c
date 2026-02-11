my_hash_sort_simple(CHARSET_INFO *cs,
			 const uchar *key, size_t len,
			 ulong *nr1, ulong *nr2)
{
  register uchar *sort_order=cs->sort_order;
  const uchar *end;


  end= skip_trailing_space(key, len);

  for (; key < (uchar*) end ; key++)
  {
    nr1[0]^=(ulong) ((((uint) nr1[0] & 63)+nr2[0]) *
	     ((uint) sort_order[(uint) *key])) + (nr1[0] << 8);
    nr2[0]+=3;
  }
}
