ndn16copy(char *from, char *to, int n)
{
  for(;n--;from+=2,to+=2)
  {
    to[1]=from[0];to[0]=from[1];
  }
}
