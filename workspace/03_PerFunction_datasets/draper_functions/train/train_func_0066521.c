i40e_dcbnl_flush_apps(struct i40e_pf *pf,
			   struct i40e_dcbx_config *old_cfg,
			   struct i40e_dcbx_config *new_cfg)
{
	struct i40e_dcb_app_priority_table app;
	int i;


	if ((pf->flags & I40E_FLAG_MFP_ENABLED) && !(pf->hw.func_caps.iscsi))
		return;

	for (i = 0; i < old_cfg->numapps; i++) {
		app = old_cfg->app[i];

		if (!i40e_dcbnl_find_app(new_cfg, &app))
			i40e_dcbnl_del_app(pf, &app);
	}
}
