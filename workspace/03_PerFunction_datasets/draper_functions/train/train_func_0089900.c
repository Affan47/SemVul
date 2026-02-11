RecomputeMLProfiles(NJ_t *NJ) {
  traversal_t traversal = InitTraversal(NJ);
  int node = NJ->root;
  while((node = TraversePostorder(node, NJ, traversal, NULL)) >= 0) {
    if (NJ->child[node].nChild == 2) {
      NJ->profiles[node] = FreeProfile(NJ->profiles[node], NJ->nPos, NJ->nConstraints);
      int *children = NJ->child[node].child;
      NJ->profiles[node] = PosteriorProfile(NJ->profiles[children[0]], NJ->profiles[children[1]],
					    NJ->branchlength[children[0]], NJ->branchlength[children[1]],
					    NJ->transmat, &NJ->rates, NJ->nPos, NJ->nConstraints);
    }
  }
  traversal = FreeTraversal(traversal, NJ);
}
