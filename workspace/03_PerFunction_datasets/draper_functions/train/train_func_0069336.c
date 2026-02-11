param_val_to_str(struct iscsi_key *keys, int idx, unsigned int val, char *str)
{
	if (keys[idx].ops->val_to_str)
		return keys[idx].ops->val_to_str(val, str);
	else
		return 0;
}
