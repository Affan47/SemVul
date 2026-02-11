microdelay(int us)
{
  volatile int j = 0;

  while(us-- > 0)
    for(j=0; j<10000; j++);
}
