is_comment(char *cp)
{
   while(*cp && isspace(*cp))
      cp++;
   if(*cp == ';' || *cp == '#' || *cp == 0 )
      return 1;
   return 0;
}
