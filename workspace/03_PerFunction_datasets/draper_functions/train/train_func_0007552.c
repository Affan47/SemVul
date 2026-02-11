MG_s_dof_copy_from_sparse(MG_S_INFO *mg_s_info,
			       const REAL *x, DOF_REAL_VEC *y)
{
  FUNCNAME("MG_s_dof_copy_from_sparse");
  int             i, j, jmax, *sort_dof, ysize;
  REAL            *yvec;

  TEST_EXIT(mg_s_info && x,"no mg_info or x\n");
  TEST_EXIT(y,"no y\n");

  sort_dof = mg_s_info->sort_dof;
  jmax = mg_s_info->dofs_per_level[mg_s_info->mg_info->mg_levels-1];
  yvec = y->vec;
  ysize = y->size;

  for (j = 0; j < jmax; j++)
  {
    i = sort_dof[j];
    TEST_EXIT(i < ysize,"i=%d too big; j=%d, y->size=%d\n", i, j, ysize);
    yvec[i] = x[j];
  }
}
