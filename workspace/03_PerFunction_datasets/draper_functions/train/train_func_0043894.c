cpd(struct child *c)
{
  int i, n;
  double t0 = now();

  srandom(kvtest_first_seed + c->childno);

  for(i = 0; !timeout[0]; i++){
    char key[512], val[512];
    if (i % CPN == 0)
      srandom(kvtest_first_seed + c->childno);
    long x = random();
    sprintf(key, "%ld", x);
    sprintf(val, "%ld", x + 1);
    aput(c, Str(key), Str(val));
  }
  n = i;

  checkasync(c, 2);

  double t1 = now();
  Json result = Json().set("total", (long) (n / (t1 - t0)))
    .set("puts", n)
    .set("puts_per_sec", n / (t1 - t0));
  printf("%s\n", result.unparse().c_str());
}
