THRandom_nextState()
{
  unsigned long *p=state;
  int j;


  if(initf == 0)
    THRandom_seed();

  left = n;
  next = state;

  for(j = n-m+1; --j; p++)
    *p = p[m] ^ TWIST(p[0], p[1]);

  for(j = m; --j; p++)
    *p = p[m-n] ^ TWIST(p[0], p[1]);

  *p = p[m-n] ^ TWIST(p[0], state[0]);
}
