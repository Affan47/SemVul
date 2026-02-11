cache_presence (state_t state)
{
  int i, num = 0;
  unsigned int sz;
  sz = (description->query_units_num + sizeof (int) * CHAR_BIT - 1)
        / (sizeof (int) * CHAR_BIT);

  state->presence_signature = XCREATENODEVEC (unsigned int, sz);
  for (i = 0; i < description->units_num; i++)
    if (units_array [i]->query_p)
      {
	int presence1_p = first_cycle_unit_presence (state, i);
	state->presence_signature[num / (sizeof (int) * CHAR_BIT)]
	  |= (!!presence1_p) << (num % (sizeof (int) * CHAR_BIT));
	num++;
      }
}
