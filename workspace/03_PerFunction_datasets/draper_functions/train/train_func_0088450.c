msp430_interrupt (int vector)
{
  int ivec;

  if (vector < 0xffe0 || vector > 0xfffful || (vector & 1))
    return -1;


  ivec = msp430_fetch_integer (vector);


  sp -= 2;
  msp430_write_integer (sp, pc, 2);

  sp -= 2;
  msp430_write_integer (sp, sr, 2);


  pc = ivec;

  alu.interrupts += 1;

  return 0;
}
