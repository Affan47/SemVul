state_addrange(st_tree_t *root, const char *var, const int min, const int max)
{
	st_tree_t	*sttmp;


	if (min > max) {
		upslogx(LOG_ERR, "state_addrange: min is superior to max! (%i, %i)",
			min, max);
		return 0;
	}


	sttmp = state_tree_find(root, var);

	if (!sttmp) {
		upslogx(LOG_ERR, "state_addrange: base variable (%s) "
			"does not exist", var);
		return 0;
	}

	return st_tree_range_add(&sttmp->range_list, min, max);
}
