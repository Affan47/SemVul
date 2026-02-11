recover_idr_add(struct dlm_rsb *r)
{
	struct dlm_ls *ls = r->res_ls;
	int rv;

	idr_preload(GFP_NOFS);
	spin_lock(&ls->ls_recover_idr_lock);
	if (r->res_id) {
		rv = -1;
		goto out_unlock;
	}
	rv = idr_alloc(&ls->ls_recover_idr, r, 1, 0, GFP_NOWAIT);
	if (rv < 0)
		goto out_unlock;

	r->res_id = rv;
	ls->ls_recover_list_count++;
	dlm_hold_rsb(r);
	rv = 0;
out_unlock:
	spin_unlock(&ls->ls_recover_idr_lock);
	idr_preload_end();
	return rv;
}
