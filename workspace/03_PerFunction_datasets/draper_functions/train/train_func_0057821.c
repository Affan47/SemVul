param_set_val(struct iscsi_key *keys, struct iscsi_param *param,
		  int idx, unsigned int *val2)
{
	if (keys[idx].ops->set_val)
		keys[idx].ops->set_val(param, idx, val2);
}
