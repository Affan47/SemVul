max_level_fct(const EL_INFO *el_info, void *data)
{
  MG_TRAVERSE_DATA *ud = (MG_TRAVERSE_DATA *)data;
  int dof, dof0, dof1, level = (int)(el_info->level);
  int dim = el_info->mesh->dim;
  EL  *el   = el_info->el;

  ud->max_level = MAX(level, ud->max_level);

  if (!(IS_LEAF_EL(el))) {
    dof   = el->child[0]->dof[N_VERTICES(dim)-1][0];
    dof0  = ud->dof_parent0[dof] = el->dof[0][0];
    dof1  = ud->dof_parent1[dof] = el->dof[1][0];
    level = ud->dof_level[dof]   = 1 + MAX(ud->dof_level[dof0],
					   ud->dof_level[dof1]);
    ud->max_dof_level = MAX(level, ud->max_dof_level);
  }
}
