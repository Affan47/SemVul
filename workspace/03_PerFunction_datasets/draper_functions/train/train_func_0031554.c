bfa_fcpim_read_throttle(struct bfa_s *bfa)
{
	struct bfa_throttle_cfg_s *throttle_cfg =
			&(BFA_DCONF_MOD(bfa)->dconf->throttle_cfg);

	return ((!bfa_dconf_get_min_cfg(bfa)) ?
	       ((throttle_cfg->is_valid == 1) ? (throttle_cfg->value) : 0) : 0);
}
