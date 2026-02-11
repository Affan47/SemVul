send_environment()
{
  int n;
  char** e;


  for (e = environ, n = 0;  *e != 0;  ++e, ++n)
    ;

  outs("env ");
  outs(itoa(n));
  outs("\n");
  for (e = environ;  *e != 0;  ++e) {
    outv(*e);
  }
}
