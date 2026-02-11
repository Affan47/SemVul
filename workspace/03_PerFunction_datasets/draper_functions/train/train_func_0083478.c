compute_procs(Table *t, Bintree *bintree) {
  if (bintree == NULL) {
    return;
  }
  if(bintree->entry->kind == ENTRY_KIND_PROC) {

    compute_proc_arg_offsets(bintree->entry);
    compute_proc_param_offsets(bintree->entry->u.procEntry.localTable->bintree, TRUE);

    bintree->entry->u.procEntry.size_local_vars = compute_proc_localvars(bintree->entry->u.procEntry.localTable, bintree->entry->aref);

    bintree->entry->u.procEntry.size_args_out = compute_proc_out_sizes(t, bintree->entry->aref);
  }
  compute_procs(t, bintree->left);
  compute_procs(t, bintree->right);
}
