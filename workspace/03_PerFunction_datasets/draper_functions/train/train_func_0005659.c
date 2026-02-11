contsize(integer obj)
{
  int i;
  long net;

  net=0;
  contloop(i,obj) {
    if (tnoun(i))
      net+=noun[i-first_noun].size;
    if (aver<AGX00)
      net+=contsize(i);
  }
  return net;
}
