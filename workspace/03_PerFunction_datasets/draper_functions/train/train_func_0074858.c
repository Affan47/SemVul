get_100_bits_from_table(uint16_t *intable, struct UNSP *read_struct) {
  uint32_t count = 1;

  while (count<0x100)
    count = (count*2)|getbit_from_table(&intable[count], read_struct);
  return count&0xff;
}
