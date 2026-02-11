get_nsubgraphs() {
   NodeVector *roots = get_subgraph_roots();
   size_t count = roots->size();
   delete roots;
   return count;
}
