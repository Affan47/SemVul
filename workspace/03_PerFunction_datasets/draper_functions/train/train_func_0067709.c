update_node_desc(sym_environment *env, bc_node *root, int change_type){

   node_desc *desc = &(root->desc);
   int i, tmp_size, colnum = env->mip->n;
   int added_colnum = env->mip->new_col_num;
   int old_colnum = colnum - added_colnum;

   if(change_type == COLS_ADDED && added_colnum > 0){
      if(desc->uind.type == EXPLICIT_LIST){
	 tmp_size = desc->uind.size;
	 if(tmp_size < colnum){
	    desc->uind.list = (int *) realloc((int *)desc->uind.list,
					      (tmp_size + added_colnum) * ISIZE);
	    for(i = 0; i < added_colnum; i++){
	       desc->uind.list[tmp_size + i] = old_colnum + i;
	    }
	    desc->uind.size += added_colnum;
	 }
      }
      if(desc->basis.basis_exists &&
	 desc->basis.extravars.type == EXPLICIT_LIST){
	 tmp_size = desc->basis.extravars.size;
	 if(tmp_size < colnum){


	    desc->basis.extravars.stat =
	       (int*)realloc((int*)desc->basis.extravars.stat,
			     (tmp_size + added_colnum) *ISIZE);
	    for(i = 0; i < added_colnum; i++){
	       desc->basis.extravars.stat[tmp_size + i] = VAR_AT_LB;
	    }
	    desc->basis.extravars.size += added_colnum;
	 }
      }
   }
}
