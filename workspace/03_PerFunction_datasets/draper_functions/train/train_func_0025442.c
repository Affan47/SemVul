TreeLength(NJ_t *NJ, bool recomputeProfiles) {
  if (recomputeProfiles) {
    traversal_t traversal2 = InitTraversal(NJ);
    int j = NJ->root;
    while((j = TraversePostorder(j, NJ, traversal2, NULL)) >= 0) {

      if (j >= NJ->nSeq && j != NJ->root)
	SetProfile(NJ, j, -1.0);
    }
    traversal2 = FreeTraversal(traversal2,NJ);
  }
  UpdateBranchLengths(NJ);
  double total_len = 0;
  int iNode;
  for (iNode = 0; iNode < NJ->maxnode; iNode++)
    total_len += NJ->branchlength[iNode];
  return(total_len);
}
