sort_group (int start)
#line 27
{
#line 27
  int i;
#line 27

#line 27
  for (i = start; i < NOPTHELP && opthelp[i].opt; i++)
#line 27
    ;
#line 27
  sort_options (start, i - start);
#line 27
  return i + 1;
#line 27
}
