doit(int i, int argc, char *argv[])
{
  int     n;
  int     prefix;
  char   *num;

  post_init();
  memset(ignore, 0, sizeof(ignore));
  if (!need_dest && i == 0) {
    i = 0;
    argc = 1;
    argv[0] = "2345";
  }
  while (i < argc) {
    num = sub_sp(argv[i]);
    if (explain == 55) {
      if (n_providers) {
	destnum.nprovider = pnum2prefix_variant(providers[0], 0);
	Strncpy(destnum.provider, getProvider(destnum.nprovider), TN_MAX_PROVIDER_LEN);
	normalizeNumber(num, &destnum, TN_NO_PROVIDER);
      }
      else
	normalizeNumber(num, &destnum, TN_ALL);
      printf("%s => %s \n", num, formatNumber("%l - %p", &destnum));
      i++;
      continue;
    }
    else if (explain == 52) {

      int     first = 1;
      char   *p;

      do {
	p = getServiceNames(first);
	if (p)
	  printf("%s\n", p);
	first = 0;
      }
      while (p);
      return;
    }
    destnum.nprovider = UNKNOWN;
    if (provider2prefix(num, &prefix))

      normalizeNumber(num, &destnum, TN_PROVIDER);
    if (table)
      printTable(num);
    else {
      n = compute(num);
      if (list)
	printList(n);
      else if (explain < 10)
	result(n);
      purge(n);
    }
    i++;
  }
  clean_up();
}
