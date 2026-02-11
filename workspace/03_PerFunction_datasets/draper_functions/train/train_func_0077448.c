libset_option_string (const char *s)
{
    if (!strcmp(s, HAC_LAG)) {
	return hac_lag_string();
    } else if (!strcmp(s, GARCH_VCV)) {
	return garch_vcv_strs[state->garch_vcv];
    } else if (!strcmp(s, ARMA_VCV)) {
	return get_arma_vcv_str(state->arma_vcv);
    } else if (!strcmp(s, HAC_KERNEL)) {
	return hac_kernel_strs[state->ropts.hkern];
    } else if (!strcmp(s, HC_VERSION)) {
	return hc_version_strs[state->ropts.hc_version];
    } else if (!strcmp(s, VECM_NORM)) {
	return vecm_norm_strs[state->vecm_norm];
    } else if (!strcmp(s, GRETL_OPTIM)) {
	return optim_strs[state->optim];
    } else if (!strcmp(s, NORMAL_RAND)) {
	return normal_rand_strs[gretl_rand_get_box_muller()];
    } else if (!strcmp(s, RNG)) {
	return RNG_strs[gretl_rand_get_sfmt()];
    } else {
	return "?";
    }
}
