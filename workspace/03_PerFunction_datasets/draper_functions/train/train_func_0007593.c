mat_vec_dowb(void *ud, int dim, const REAL *x, REAL *y)
{
  FUNCNAME("mat_vec_dowb");
  DOF_REAL_D_VEC  dof_x = {nil, nil, "x", 0, nil, nil, nil};
  DOF_REAL_D_VEC  dof_y = {nil, nil, "y", 0, nil, nil, nil};
  struct mv_data  *data     = (struct mv_data *)ud;
  const S_CHAR    *b        = data->bound ? data->bound->vec : nil;
  const DOF_ADMIN *admin    = data->matrix->row_fe_space->admin;
  REAL_D          *xd = (REAL_D *) x, *yd = (REAL_D *) y;

  TEST_EXIT(dim == DIM_OF_WORLD*admin->size_used,
"argument dim != DIM_OF_WORLD*data->matrix->row_fe_space->admin->size_used\n");

  dof_x.fe_space = data->matrix->col_fe_space;
  dof_y.fe_space = data->matrix->row_fe_space;

  dof_x.size = dof_y.size = dim/DIM_OF_WORLD;
  dof_x.vec = xd;
  dof_y.vec = yd;

  dof_mv_dowb(data->transpose, data->matrix, &dof_x, &dof_y);

  if (b)
  {
    FOR_ALL_DOFS(admin, if (b[dof] > 0)  COPY_DOW(xd[dof], yd[dof]));
  }
  return(0);
}
