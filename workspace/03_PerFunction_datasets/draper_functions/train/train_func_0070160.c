index_to_bitboard(int index, Bitboard mask) {
    int i, j, bits = count_1s(mask);
    Bitboard result = 0ULL;
    for(i = 0; i < bits; i++) {
      j = pop_1st_bit(&mask);
      if(index & (1 << i)) result |= (1ULL << j);
    }
    return result;
  }
