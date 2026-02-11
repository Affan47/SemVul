check_end(const char *p)
{
   if (!p)
      return 0;
   while (isspace(*p))
      ++p;
   if (!*p || (p[0] == 'G' && p[1] == 'M' && p[2] == 'T'))
      return 1;
   else
      return 0;
}
