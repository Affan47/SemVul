numuse (const Table *t, int *narray, int *nhash) {
  int nums[MAXBITS+1];
  int i, lg;
  int totaluse = 0;

  for (i=0, lg=0; lg<=MAXBITS; lg++) {
    int ttlg = twoto(lg);
    if (ttlg > t->sizearray) {
      ttlg = t->sizearray;
      if (i >= ttlg) break;
    }
    nums[lg] = 0;
    for (; i<ttlg; i++) {
      if (!ttisnil(&t->array[i])) {
        nums[lg]++;
        totaluse++;
      }
    }
  }
  for (; lg<=MAXBITS; lg++) nums[lg] = 0;
  *narray = totaluse;

  i = sizenode(t);
  while (i--) {
    Node *n = &t->node[i];
    if (!ttisnil(gval(n))) {
      int k = arrayindex(gkey(n));
      if (k >= 0) {
        nums[luaO_log2(k-1)+1]++;
        (*narray)++;
      }
      totaluse++;
    }
  }
  computesizes(nums, totaluse, narray, nhash);
}
