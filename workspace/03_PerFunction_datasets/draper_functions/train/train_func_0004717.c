do_ifdef(p, which)
char * p;
int which;
{
   char * nm;
   char * s;
   struct varrec * curr;

   while( *p == ' ' || *p == '\t') p++;
   nm = p;

   for(curr=varlist; curr ; curr = curr->next)
   {
      s = curr->name;
      p = nm;
      while( *p == *s ) { p++; s++; }
      if( *s == '\0' && *p <= ' ' )
	 break;
   }
   state[iflevel] = keeptext;
   iflevel++;

   p=nm;
   s=names[iflevel];
   while(*p > ' ') *s++ = *p++;
   *s = '\0';

   if( curr == 0 )
   {
      if( unknown_stat == 0 )
      {
         if( keeptext ) keeptext |= 2;
         return 0;
      }
      if( keeptext )
         keeptext = (unknown_stat == which);
      return 1;
   }
   if( keeptext )
      keeptext = (curr->state == which);
   return 1;
}
