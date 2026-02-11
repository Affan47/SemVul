ndn32copy(char *from, char *to, int n)
{
  for(;n--;from+=4,to+=4)
  {
    to[3]=from[0];to[2]=from[1];to[1]=from[2];to[0]=from[3];
  }
}
