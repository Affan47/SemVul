volt2b1(struct child *c, struct async *a, bool, const Str &val)
{
  int k = atoi(a->key);
  int v = atoi(val.s);
  if((v % 2) == 1){
    char key[100], val[100];
    sprintf(key, "%d-%ld", k, random() % VOLT2INTS);
    for (int i = strlen(key); i < 50; i++)
      key[i] = ' ';
    sprintf(val, "%ld", random());
    aput(c, Str(key, 50), Str(val));
  }
}
