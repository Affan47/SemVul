gfs_electro_hydro_init (GfsElectroHydro * object)
{
  GfsDomain * domain = GFS_DOMAIN (object);
  static gchar name[][3] = {"Ex", "Ey", "Ez"};
  static gchar desc[][34] = {"x component of the electric field",
			     "y component of the electric field",
			     "z component of the electric field"};
  FttComponent c;

  object->phi = gfs_domain_add_variable (domain, "Phi", "Electric potential");
  object->phi->centered = TRUE;
  object->rhoe = gfs_variable_new (gfs_variable_tracer_class(), domain,
				   "Rhoe", "Volumetric charge density");
  object->rhoe->units = -3.;
  domain->variables = g_slist_append (domain->variables, object->rhoe);

  for (c = 0; c < FTT_DIMENSION; c++) {
    object->E[c] = gfs_domain_add_variable (domain , name[c], desc[c]);
    object->E[c]->units = -1.;
  }
  gfs_variable_set_vector (object->E, FTT_DIMENSION);

  gfs_multilevel_params_init (&object->electric_projection_params);
  object->perm = gfs_function_new (gfs_function_class (), 1.);
  gfs_function_set_units (object->perm, -1.);


  for (c = 0; c < FTT_DIMENSION; c++) {
    GfsBc * bc = gfs_bc_new (gfs_bc_neumann_class(), object->E[c], FALSE);
    bc->bc      = (FttFaceTraverseFunc) setting_E_from_phi;
    bc->face_bc = (FttFaceTraverseFunc) face_setting_E_from_phi;
    gfs_variable_set_default_bc (object->E[c], bc);
  }
}
