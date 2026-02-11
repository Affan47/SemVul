maximum_check_val(struct iscsi_key *key, unsigned int *val)
{
	int err = 0;

	if (*val < key->min || key->max < *val) {
		*val = key->max;
		err = -EINVAL;
	}

	return err;
}
