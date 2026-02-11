RLUnCompVram(armcpu_t* cpu)
{
  int i;
  int len;
  int byteCount;
  int byteShift;
  u32 writeValue;
  u32 source = cpu->R[0];
  u32 dest = cpu->R[1];

  u32 header = MMU_read32(cpu->proc_ID, source);
  source += 4;

  if(((source & 0xe000000) == 0) ||
     ((source + ((header >> 8) & 0x1fffff)) & 0xe000000) == 0)
    return 0;

  len = header >> 8;
  byteCount = 0;
  byteShift = 0;
  writeValue = 0;

  while(len > 0) {
    u8 d = MMU_read8(cpu->proc_ID, source++);
    int l = d & 0x7F;
    if(d & 0x80) {
      u8 data = MMU_read8(cpu->proc_ID, source++);
      l += 3;
      for(i = 0;i < l; i++) {
        writeValue |= (data << byteShift);
        byteShift += 8;
        byteCount++;

        if(byteCount == 2) {
          MMU_write16(cpu->proc_ID, dest, writeValue);
          dest += 2;
          byteCount = 0;
          byteShift = 0;
          writeValue = 0;
        }
        len--;
        if(len == 0)
          return 0;
      }
    } else {
      l++;
      for(i = 0; i < l; i++) {
        writeValue |= (MMU_read8(cpu->proc_ID, source++) << byteShift);
        byteShift += 8;
        byteCount++;
        if(byteCount == 2) {
          MMU_write16(cpu->proc_ID, dest, writeValue);
          dest += 2;
          byteCount = 0;
          byteShift = 0;
          writeValue = 0;
        }
        len--;
        if(len == 0)
          return 0;
      }
    }
  }
  return 1;
}
