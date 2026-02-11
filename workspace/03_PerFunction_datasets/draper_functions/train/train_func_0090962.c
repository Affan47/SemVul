apol_infoflow_analysis_set_dir(const apol_policy_t * p, apol_infoflow_analysis_t * ia, unsigned int dir)
{
	switch (dir) {
	case APOL_INFOFLOW_IN:
	case APOL_INFOFLOW_OUT:
	case APOL_INFOFLOW_BOTH:
	case APOL_INFOFLOW_EITHER:
	{
		ia->direction = dir;
		break;
	}
	default:
	{
		ERR(p, "%s", strerror(EINVAL));
		return -1;
	}
	}
	return 0;
}
