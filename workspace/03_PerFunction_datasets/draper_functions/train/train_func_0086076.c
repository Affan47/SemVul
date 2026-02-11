bitset_init (bitset bset, bitset_bindex n_bits, enum bitset_type type)
{
  if (bitset_stats_enabled)
    return bitset_stats_init (bset, n_bits, type);

  switch (type)
    {
    default:
      abort ();

    case BITSET_ARRAY:
      return abitset_init (bset, n_bits);

    case BITSET_LIST:
      return lbitset_init (bset, n_bits);

    case BITSET_TABLE:
      return ebitset_init (bset, n_bits);

    case BITSET_VARRAY:
      return vbitset_init (bset, n_bits);
    }
}
