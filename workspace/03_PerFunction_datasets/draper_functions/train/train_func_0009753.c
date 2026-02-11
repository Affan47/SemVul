dscracts(void)
#else
void dscracts()
#endif
{
  int i;

  for (i = HERO+1; i <= ACTMAX; i++)
    if (acts[i-ACTMIN].loc == cur.loc &&
	acts[i-ACTMIN].describe)
      describe(i);


  for (i = HERO; i <= ACTMAX; i++)
    acts[i-ACTMIN].describe = TRUE;
}
