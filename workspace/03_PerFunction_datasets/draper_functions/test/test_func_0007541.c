free_dof_ptrs(DOF **ptrs, MESH *mesh)
{
  FUNCNAME("free_dof_ptrs");
  int      n;
  MESH_MEM_INFO *mem_info;

  DEBUG_TEST_EXIT(ptrs,"ptrs=nil\n");
  DEBUG_TEST_EXIT(mesh, "mesh=nil\n");
  DEBUG_TEST_EXIT(mesh->mem_info,
	      "mesh \"%s\": mesh->mem_info=nil\n", mesh->name);
  n = mesh->n_node_el;
  if (n <= 0)
    return;

  DEBUG_TEST_EXIT(n <= max_dof_ptrs[mesh->dim],
	      "mesh \"%s\": too many nodes: %d > %d\n",
	      mesh->name, n, max_dof_ptrs[mesh->dim]);

  mem_info = (MESH_MEM_INFO*)(mesh->mem_info);

  DEBUG_TEST_EXIT(mem_info->dof_ptrs,
	      "mesh \"%s\": mesh->mem_info->dof_ptrs=nil\n", mesh->name);

  freeMemory((void *)ptrs, mem_info->dof_ptrs);
  return;
}
