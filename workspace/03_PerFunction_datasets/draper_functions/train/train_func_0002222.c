trim_warm_tree(sym_environment *env, bc_node *n)
{
   int i, not_pruned = 0;


   if (n->bobj.child_num == 0)
      return(0);


   for (i = n->bobj.child_num - 1; i >= 0; i--)
      if (n->children[i]->node_status != NODE_STATUS__PRUNED)
	 if (++not_pruned > 1)
	    break;
   if (not_pruned == 0)
      return(0);
   if (not_pruned == 1){
      for (i = n->bobj.child_num - 1; i >= 0; i--)
	 if (n->children[i]->node_status != NODE_STATUS__PRUNED){
	    trim_warm_tree(env, n->children[i]);
	    break;
	 }
      return(0);
   }


   for (i = n->bobj.child_num - 1; i >= 0; i--)
      if (n->children[i]->lower_bound + env->par.tm_par.granularity <
	  env->warm_start->ub)
	 break;


   if (i < 0){

      for (i = n->bobj.child_num - 1; i >= 0; i--)
	 free_subtree(n->children[i]);

      FREE(n->children);
      n->bobj.child_num = 0;
#ifndef MAX_CHILDREN_NUM
      FREE(n->bobj.sense);
      FREE(n->bobj.rhs);
      FREE(n->bobj.range);
      FREE(n->bobj.branch);
#endif
   }else{

      for (i = n->bobj.child_num - 1; i >= 0; i--)
	 trim_warm_tree(env, n->children[i]);
   }
   return(0);
}
