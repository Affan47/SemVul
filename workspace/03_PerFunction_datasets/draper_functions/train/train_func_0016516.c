subtree_depth (const wfa_t *wfa, int local_root)


{
   int max_depth = 0;
   int label;

   for (label = 0; label < MAXLABELS; label++)
      if (isedge (wfa->tree [local_root][label]))
	 max_depth = max (max_depth,
			  subtree_depth (wfa,
					 wfa->tree [local_root][label]) + 1);
   return max_depth;
}
