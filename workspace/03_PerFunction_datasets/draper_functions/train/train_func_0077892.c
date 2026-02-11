protohash_init(void)
{
   if (protohash)
      return TRUE;

   protohash = g_hash_table_new_full(g_str_hash,
                                     g_str_equal,
                                     freehash,
                                     freehash);
   return protohash != NULL;
}
