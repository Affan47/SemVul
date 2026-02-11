cleanup(int keepnum) {
  struct dirent **list;
  int i, n;

  n = scandir(".",
	      &list,
	      (int (*)(struct dirent *)) selector,
	      (int (*)(void const *, void const *)) sorter);

  if (n > keepnum) {
    for (i = 0; i < n - keepnum; i++) {
      char buf[1024];
      sprintf(buf, "./%s", list[i]->d_name);
      remove(buf);
    }
  }

  for (i = 0; i < n; i++)
    free(list[i]);
  free(list);
}
