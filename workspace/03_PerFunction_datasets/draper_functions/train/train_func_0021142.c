print_region_statistics (int *s1, int s1_sz, int *s2, int s2_sz)
{
  int i;


  for (i = 1; i < s2_sz; i++)
    {
      int n1, n2;

      n2 = s2[i];

      if (n2 == 0)
	continue;

      if (i >= s1_sz)
	n1 = 0;
      else
	n1 = s1[i];

      fprintf (sched_dump, ";; Region extension statistics: size %d: " \
	       "was %d + %d more\n", i + 1, n1, n2 - n1);
    }
}
