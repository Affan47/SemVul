same(int a, int b)
{
  int match;


  match = NO;

  if (a == b || a > NUM_ALL_BLOCKS || b > NUM_ALL_BLOCKS)
    match = YES;

  return(match);
}
