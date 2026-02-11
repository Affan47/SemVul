load_tree(long treei)
{
  long j, nextnode;
  boolean recompute = false;
  node *dummy;

  for (j = spp - 1; j >= 1; j--)
    re_move(treenode[j], &dummy, &root, recompute, treenode, &grbg,
              zeros, zeros2);
  root = treenode[0];
  recompute = true;
  add(treenode[0], treenode[1], treenode[spp], &root, recompute,
    treenode, &grbg, zeros, zeros2);
  nextnode = spp + 2;
  for (j = 3; j <= spp; j++) {
    if (bestrees[treei].btree[j - 1] > 0)
      add(treenode[bestrees[treei].btree[j - 1] - 1], treenode[j - 1],
            treenode[nextnode++ - 1], &root, recompute, treenode, &grbg,
            zeros, zeros2);
    else
      add(treenode[treenode[-bestrees[treei].btree[j-1]-1]->back->index-1],
            treenode[j - 1], NULL, &root, recompute, treenode, &grbg,
            zeros, zeros2);
  }
}
