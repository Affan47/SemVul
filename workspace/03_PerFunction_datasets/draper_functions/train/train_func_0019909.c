lam_ssi_coll_lam_basic_init(MPI_Comm comm,
			    const lam_ssi_coll_actions_1_1_0_t **new_actions)
{


  comm->c_ssi_coll_data = NULL;

  if (LAM_IS_INTER(comm)) {


    *new_actions = &lam_basic_inter_functions;
  }

  if (lam_ssi_coll_verbose >= 10)
    lam_debug(lam_ssi_coll_did, "lam_basic: init communicator %s",
	      comm->c_name);
  return 0;
}
