generic_crc(int algo, int position, const uint8_t *data_src)
{
  switch(algo)
  {
    case ALGO_AWARD:
      brute_award(get32(position,data_src));
      break;
    case ALGO_TOSHIBA:
      brute_toshiba(get32(position,data_src));
      break;
  }
}
