inherit_lagrange_parametric(MESH *slave)
{
  FUNCNAME("inherit_lagrange_parametric");
  MESH                *master;
  PARAMETRIC          *m_parametric;
  LAGRANGE_PARAM_DATA *m_data;
  DOF_INT_VEC         *dof_connection;
  DOF_REAL_D_VEC      *m_coords, *s_coords;
  DOF_UCHAR_VEC       *m_t_coords, *s_t_coords;
  REAL_D              *m_coord_vec, *s_coord_vec;
  U_CHAR              *m_t_coord_vec, *s_t_coord_vec;
  int                 *master_dofs;

  TEST_EXIT(slave, "No slave mesh given!\n");

  master = ((MESH_MEM_INFO *)slave->mem_info)->master;
  TEST_EXIT(master, "'%s' is not a slave mesh!\n", NAME(slave));

  m_parametric = master->parametric;
  TEST_EXIT(m_parametric, "'%s' is not a parametric mesh!\n", NAME(master));

  m_data = (LAGRANGE_PARAM_DATA *)m_parametric->data;


  use_lagrange_parametric(slave, m_data->coords->fe_space->bas_fcts->degree,
			  m_data->n_proj, m_parametric->not_all);


  m_coords = get_lagrange_coords(master);
  s_coords = get_lagrange_coords(slave);
  m_coord_vec = m_coords->vec;
  s_coord_vec = s_coords->vec;

  dof_connection = get_dof_int_vec("DOF connection", s_coords->fe_space);
  get_slave_dof_mapping(m_coords->fe_space, dof_connection);

  master_dofs = dof_connection->vec;

  if(m_parametric->not_all) {
    m_t_coords = get_lagrange_coord_flags(master);
    s_t_coords = get_lagrange_coord_flags(slave);

    m_t_coord_vec = m_t_coords->vec;
    s_t_coord_vec = s_t_coords->vec;

    FOR_ALL_DOFS(s_coords->fe_space->admin,
		 COPY_DOW(m_coord_vec[master_dofs[dof]], s_coord_vec[dof]);
		 s_t_coord_vec[dof] = m_t_coord_vec[master_dofs[dof]];
		 );
  }
  else {
    FOR_ALL_DOFS(s_coords->fe_space->admin,
		 COPY_DOW(m_coord_vec[master_dofs[dof]], s_coord_vec[dof]);
		 );
  }


  free_dof_int_vec(dof_connection);

  return;
}
