get_dof(MESH *mesh, int position)
{
  FUNCNAME("get_dof");
  DOF_ADMIN *admin;
  DOF     *dof;
  int     i, j, n, n0, ndof;

  ndof = mesh->n_dof[position];
  if (ndof <= 0) return(nil);

  dof = AI_get_dof_memory(mesh, position);

  for (i = 0; i < mesh->n_dof_admin; i++) {
    admin = mesh->dof_admin[i];
    DEBUG_TEST_EXIT(admin, "mesh \"%s\": no dof_admin[%d]\n", mesh->name, i);

    n  = admin->n_dof[position];
    n0 = admin->n0_dof[position];

    DEBUG_TEST_EXIT(n+n0 <= ndof,
		"dof_admin \"%s\": n=%d, n0=%d too large: ndof=%d\n",
		admin->name, n, n0, ndof);

    for (j = 0; j < n; j++)
      dof[n0+j] = get_dof_index(admin);
  }

  return(dof);
}
