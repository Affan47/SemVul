gres_gresid_to_gresname(uint32_t gres_id, char* gres_name,
				   int gres_name_len)
{
	ListIterator iter;
	gres_slurmd_conf_t *gres_slurmd_conf;
	int rc = SLURM_SUCCESS;
	int      found = 0;

	if (gres_conf_list == NULL) {


		info("%s--The gres_conf_list is NULL!!!\n", __FUNCTION__);
		snprintf(gres_name, gres_name_len, "%u", gres_id);
		return rc;
	}

	iter = list_iterator_create(gres_conf_list);
	while ((gres_slurmd_conf = (gres_slurmd_conf_t *) list_next(iter))) {
		if (gres_slurmd_conf->plugin_id != gres_id)
			continue;
		strncpy(gres_name, gres_slurmd_conf->name, gres_name_len);
		found = 1;
		break;
	}
	list_iterator_destroy(iter);

	if (!found)
		snprintf(gres_name, gres_name_len, "%u", gres_id);

	return rc;
}
