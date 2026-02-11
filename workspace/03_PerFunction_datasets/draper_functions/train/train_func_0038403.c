update_sound_reg(void) {
  int i;
  for(i=0xff10;i<=0xFF3F;i++)
    write_sound_reg(i,himem[i-0xFEA0]);
}
