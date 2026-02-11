get_HB_precon_s(const FE_SPACE *fe_space,
			      const DOF_SCHAR_VEC *bound,
			      int use_get_bound, int info)
{
    PRECON  *precon;
    HB_DATA *data;

    if (bound && (bound->fe_space != fe_space)) {
	ERROR("different fe spaces ?\n");
	return(nil);
    }

    precon = MEM_CALLOC(1, PRECON);
    data   = MEM_CALLOC(1, HB_DATA);

    data->fe_space = fe_space;
    if (!(data->bound_dv = bound))
      data->use_get_bound = use_get_bound;

    data->info     = info;

    precon->precon_data = data;
    precon->init_precon = init_HB_precon;
    precon->precon      = HB_precon_s;
    precon->exit_precon = exit_HB_precon;

    return(precon);
}
