sched_info_free(__isl_take struct isl_sched_info *info)
{
	if (!info)
		return;
	isl_vec_free(info->cst);
	free(info->is_cst);
	free(info);
}
