poldiff_terule_get_stats(const poldiff_t * diff, size_t stats[5], unsigned int idx)
{
	if (diff == NULL || stats == NULL) {
		ERR(diff, "%s", strerror(EINVAL));
		errno = EINVAL;
		return;
	}
	stats[0] = diff->terule_diffs[idx]->num_added;
	stats[1] = diff->terule_diffs[idx]->num_removed;
	stats[2] = diff->terule_diffs[idx]->num_modified;
	stats[3] = diff->terule_diffs[idx]->num_added_type;
	stats[4] = diff->terule_diffs[idx]->num_removed_type;
}
