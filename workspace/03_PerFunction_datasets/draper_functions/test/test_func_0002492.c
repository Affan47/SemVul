gt_sain_fast_assignSstarnames(unsigned long totallength,
                                          unsigned long countSstartype,
                                          unsigned long *suftab,
                                          unsigned long numberofnames,
                                          unsigned long nonspecialentries)
{
  unsigned long *suftabptr, *secondhalf = suftab + countSstartype;

  if (numberofnames < countSstartype)
  {
    unsigned long currentname = numberofnames + 1;

    for (suftabptr = suftab + nonspecialentries - 1; suftabptr >= suftab;
         suftabptr--)
    {
      unsigned long position;

      if ((position = *suftabptr) >= totallength)
      {
        position -= totallength;
        gt_assert(currentname > 0);
        currentname--;
      }
      if (currentname <= numberofnames)
      {
        secondhalf[GT_DIV2(position)] = currentname;
      }
    }
  } else
  {
    for (suftabptr = suftab; suftabptr < suftab + nonspecialentries;
         suftabptr++)
    {
      if (*suftabptr >= totallength)
      {
        *suftabptr -= totallength;
      }
    }
  }
}
