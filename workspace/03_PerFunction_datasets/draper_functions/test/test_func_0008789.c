make_lanmpw(char *p, char *lm, int len)
{
   int i;

   for (i=0; i < 15; i++) lm[i] = 0;
   for (i=0; i < len; i++) lm[i] = toupper(p[i]);
}
