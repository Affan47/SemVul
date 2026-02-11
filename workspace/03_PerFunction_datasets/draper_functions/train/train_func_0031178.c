prepare_vimvar(idx, save_tv)
    int		idx;
    typval_T	*save_tv;
{
    *save_tv = vimvars[idx].vv_tv;
    if (vimvars[idx].vv_type == VAR_UNKNOWN)
	hash_add(&vimvarht, vimvars[idx].vv_di.di_key);
}
