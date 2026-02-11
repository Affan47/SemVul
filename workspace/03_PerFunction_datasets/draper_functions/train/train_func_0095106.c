ZopfliLengthLimitedCodeLengths(
    const size_t* frequencies, int n, int maxbits, unsigned* bitlengths) {
  NodePool pool;
  int i;
  int numsymbols = 0;
  int numBoundaryPMRuns;


  Node* (*lists)[2];


  Node* leaves = (Node*)malloc(n * sizeof(*leaves));


  for (i = 0; i < n; i++) {
    bitlengths[i] = 0;
  }


  for (i = 0; i < n; i++) {
    if (frequencies[i]) {
      leaves[numsymbols].weight = frequencies[i];
      leaves[numsymbols].count = i;
      numsymbols++;
    }
  }


  if ((1 << maxbits) < numsymbols) {
    free(leaves);
    return 1;
  }
  if (numsymbols == 0) {
    free(leaves);
    return 0;
  }
  if (numsymbols == 1) {
    bitlengths[leaves[0].count] = 1;
    free(leaves);
    return 0;
  }


  qsort(leaves, numsymbols, sizeof(Node), LeafComparator);


  pool.size = 2 * maxbits * (maxbits + 1);
  pool.nodes = (Node*)malloc(pool.size * sizeof(*pool.nodes));
  pool.next = pool.nodes;
  for (i = 0; i < pool.size; i++) {
    pool.nodes[i].inuse = 0;
  }

  lists = (Node* (*)[2])malloc(maxbits * sizeof(*lists));
  InitLists(&pool, leaves, maxbits, lists);


  numBoundaryPMRuns = 2 * numsymbols - 4;
  for (i = 0; i < numBoundaryPMRuns; i++) {
    char final = i == numBoundaryPMRuns - 1;
    BoundaryPM(lists, maxbits, leaves, numsymbols, &pool, maxbits - 1, final);
  }

  ExtractBitLengths(lists[maxbits - 1][1], leaves, bitlengths);

  free(lists);
  free(leaves);
  free(pool.nodes);
  return 0;
}
