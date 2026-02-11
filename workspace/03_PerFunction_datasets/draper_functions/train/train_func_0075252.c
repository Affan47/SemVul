initbestrees(bestelm *bestrees, long maxtrees, boolean glob)
{

  long i;

  if (glob)
    for (i = 0; i < maxtrees; i++)
      bestrees[i].gloreange = false;
  else
    for (i = 0; i < maxtrees; i++)
      bestrees[i].locreange = false;
}
