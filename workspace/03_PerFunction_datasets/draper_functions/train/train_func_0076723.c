FCEU_MemoryRand(uint8 *ptr, uint32 size)
{
 int x=0;
 while(size)
 {
  *ptr=(x&4)?0xFF:0x00;
  x++;
  size--;
  ptr++;
 }
}
