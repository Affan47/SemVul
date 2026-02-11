xfs_log_get_max_trans_res(
	struct xfs_mount	*mp,
	struct xfs_trans_res	*max_resp)
{
	struct xfs_trans_res	*resp;
	struct xfs_trans_res	*end_resp;
	int			log_space = 0;
	int			attr_space;

	attr_space = xfs_log_calc_max_attrsetm_res(mp);

	resp = (struct xfs_trans_res *)M_RES(mp);
	end_resp = (struct xfs_trans_res *)(M_RES(mp) + 1);
	for (; resp < end_resp; resp++) {
		int		tmp = resp->tr_logcount > 1 ?
				      resp->tr_logres * resp->tr_logcount :
				      resp->tr_logres;
		if (log_space < tmp) {
			log_space = tmp;
			*max_resp = *resp;
		}
	}

	if (attr_space > log_space) {
		*max_resp = M_RES(mp)->tr_attrsetm;
		max_resp->tr_logres = attr_space;
	}
}
