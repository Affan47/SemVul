hashdata_to_string(Hash_data *hashdata)
{
  static char buffer[BUFFER_SIZE];
  int n = 0;
  int k;


  for (k = NUM_HASHVALUES - 1; k >= 0; k--) {
    n += sprintf(buffer + n, HASHVALUE_PRINT_FORMAT,
		 HASHVALUE_NUM_DIGITS, hashdata->hashval[k]);
    gg_assert(n < BUFFER_SIZE);
  }

  return buffer;
}
