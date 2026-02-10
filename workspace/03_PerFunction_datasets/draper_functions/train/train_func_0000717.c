free_dof(DOF *dof, MESH *mesh, int position, const int is_coarse_dof)
{
  FUNCNAME("free_dof");

  DOF_ADMIN *admin;
  int     i, j, n, n0, ndof;
  MESH_MEM_INFO* mem_info;

  DEBUG_TEST_EXIT(mesh, "mesh=nil\n");
  mem_info = (MESH_MEM_INFO*)mesh->mem_info;
  DEBUG_TEST_EXIT(mem_info,"mesh \"%s\": mesh->mem_info=nil\n", mesh->name);

  DEBUG_TEST_EXIT(position >= 0 && position < N_NODE_TYPES,
	      "mesh \"%s\": unknown position %d\n",mesh->name, position);

  ndof = mesh->n_dof[position];

  DEBUG_TEST_EXIT(!ndof || dof,
	      "dof = nil, but ndof=%d\n", ndof);
  DEBUG_TEST_EXIT(ndof || !dof,
	      "dof != nil, but ndof=0\n");

  DEBUG_TEST_EXIT(mem_info->dofs[position],
	      "mesh \"%s\": no memory management present for %d DOFs.",
	      mesh->name, position);

  for (i = 0; i < mesh->n_dof_admin; i++) {
    admin = mesh->dof_admin[i];
    DEBUG_TEST_EXIT(admin, "mesh \"%s\": no dof_admin[%d]\n", mesh->name, i);

    n  = admin->n_dof[position];
    n0 = admin->n0_dof[position];

    DEBUG_TEST_EXIT(n+n0 <= ndof,
		"dof_admin \"%s\": n=%d, n0=%d too large: ndof=%d\n",
		admin, n, n0, ndof);

    if(!(admin->preserve_coarse_dofs && is_coarse_dof))
      for (j = 0; j < n; j++) {
	free_dof_index(admin, dof[n0+j]);
	dof[n0+j] = -1;
      }
  }

  if(!is_coarse_dof) {

    freeMemory((void *)dof, mem_info->dofs[position]);
  }

  return;
}
