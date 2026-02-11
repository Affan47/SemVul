RandomLevelSL(l)
     SkipList l;
{
  register int level = 0;

  while(rand() < P_25)
    {
      level++;
    }

  return (level > MaxLevel ? MaxLevel : level);
}
