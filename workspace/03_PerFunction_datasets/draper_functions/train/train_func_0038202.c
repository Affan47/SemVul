PrintStats(Data *data, uint64_t headerBits)
  {
  uint8_t   n;
  uint64_t  bits = 0, size = 0;

  for(n = 0 ; n != data->nThreads ; ++n)
    {
    bits += data[n].S.bits;
    size += data[n].S.size;
    }

  printf("------------------------------------------------------\n");
  printf("| TOTAL   | %-13"PRIu64" | %-13"PRIu64" | %-8.4lf |\n", size, bits /
  8, (double) bits / 8 / size);
  printf("------------------------------------------------------\n");
  }
