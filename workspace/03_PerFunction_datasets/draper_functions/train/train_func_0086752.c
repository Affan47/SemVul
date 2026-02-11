volt2a(struct child *c)
{
  int i, j, n = 0;
  double t0 = now(), t1;

  srandom(kvtest_first_seed + c->childno);


  int *keys = (int *) malloc(sizeof(int) * VOLT2N);
  always_assert(keys);
  for(i = 0; i < VOLT2N; i++)
    keys[i] = i;
  for(i = 0; i < VOLT2N; i++){
    int x = random() % VOLT2N;
    int tmp = keys[i];
    keys[i] = keys[x];
    keys[x] = tmp;
  }

  int subkeys[VOLT2INTS];
  for(i = 0; i < VOLT2INTS; i++)
    subkeys[i] = i;
  for(i = 0; i < VOLT2INTS; i++){
    int x = random() % VOLT2INTS;
    int tmp = subkeys[i];
    subkeys[i] = subkeys[x];
    subkeys[x] = tmp;
  }

  for(i = 0; i < VOLT2N; i++){
    for(j = 0; j < VOLT2INTS; j++){
      char val[32], key[100];
      int k;
      sprintf(key, "%d-%d", keys[i], subkeys[j]);
      for(k = strlen(key); k < 50; k++)
        key[k] = ' ';
      key[50] = '\0';
      sprintf(val, "%ld", random());
      aput(c, Str(key), Str(val));
      n++;
    }
  }
  checkasync(c, 2);
  t1 = now();

  free(keys);
  Json result = Json().set("total", (long) (n / (t1 - t0)));
  printf("%s\n", result.unparse().c_str());
}
