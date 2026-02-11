_eef_count_one_bits (eef_data_t data)
{
  eef_data_t mask = 1;
  gint cnt = 0;

  while (mask)
	{
	  if (data & mask)
		cnt++;
	  mask <<= 1;
	}
  return cnt;
}
