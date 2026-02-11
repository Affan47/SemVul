cut_ws_tree_level(sym_environment *env, bc_node *root, int level,
		       problem_stat *stat, int change_type)
{

   int i;
   if(root){
      if (root->node_status != NODE_STATUS__CANDIDATE){
	 stat->analyzed++;
      }

      if(root->bc_level < level){
	 for (i = 0; i < root->bobj.child_num; i++){
	    root->children[i]->bc_index = ++stat->tree_size;
	    stat->created++;
	 }
	 for (i = root->bobj.child_num - 1; i >= 0; i--){
	    cut_ws_tree_level(env, root->children[i], level, stat, change_type);
	 }
      }
      if(root->bc_level == level){
	 for (i = root->bobj.child_num - 1; i >= 0; i--)
	    ws_free_subtree(env, root->children[i], change_type, TRUE, FALSE);
	 root->bobj.child_num = 0;

	 if (root->node_status == NODE_STATUS__BRANCHED_ON){
	    root->node_status = NODE_STATUS__WARM_STARTED;
	 }
      }
   }
}
