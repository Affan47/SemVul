free_node_desc(node_desc **desc)
{
   if (*desc){
      node_desc *n = *desc;
      FREE(n->cutind.list);
      FREE(n->uind.list);
      if (n->nf_status == NF_CHECK_AFTER_LAST ||
	  n->nf_status == NF_CHECK_UNTIL_LAST)
	 FREE(n->not_fixed.list);
      if (n->basis.basis_exists){
	 FREE(n->basis.basevars.list);
	 FREE(n->basis.basevars.stat);
	 FREE(n->basis.extravars.list);
	 FREE(n->basis.extravars.stat);
	 FREE(n->basis.baserows.list);
	 FREE(n->basis.baserows.stat);
	 FREE(n->basis.extrarows.list);
	 FREE(n->basis.extrarows.stat);
      }
      if (n->desc_size > 0)
	 FREE(n->desc);
      if (n->bnd_change) {
         FREE(n->bnd_change->index);
         FREE(n->bnd_change->lbub);
         FREE(n->bnd_change->value);
         FREE(n->bnd_change);
      }
      FREE(*desc);
   }
}
