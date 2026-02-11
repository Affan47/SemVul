update_crc(uint32_t crc_accum,
           const char *data_blk_ptr,
           int data_blk_size)
{
  int i, j;
  static int initialized = 0;

  if(initialized == 0){
    initialized = 1;
    gen_crc_table();
  }

  for ( j = 0;  j < data_blk_size;  j++ ){
    i = ( (uint32_t) ( crc_accum >> 24) ^ *data_blk_ptr++ ) & 0xff;
    crc_accum = ( crc_accum << 8 ) ^ crc_table[i];
  }
  return crc_accum;
}
