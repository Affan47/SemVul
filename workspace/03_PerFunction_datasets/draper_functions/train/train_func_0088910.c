classify_counts(u64* mem) {

  u32 i = MAP_SIZE >> 3;

  while (i--) {


    if (*mem) {

      u8* mem8 = (u8*)mem;

      mem8[0] = count_class_lookup[mem8[0]];
      mem8[1] = count_class_lookup[mem8[1]];
      mem8[2] = count_class_lookup[mem8[2]];
      mem8[3] = count_class_lookup[mem8[3]];
      mem8[4] = count_class_lookup[mem8[4]];
      mem8[5] = count_class_lookup[mem8[5]];
      mem8[6] = count_class_lookup[mem8[6]];
      mem8[7] = count_class_lookup[mem8[7]];

    }

    mem++;

  }

}
