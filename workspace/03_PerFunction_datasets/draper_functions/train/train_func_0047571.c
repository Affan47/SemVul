gar_find_subdiv_by_idx(struct gar_subfile *gsub,
						int fromlevel, int idx)
{
	int i = fromlevel;
	struct gar_subdiv *sd;

	for (; i < gsub->nlevels; i++) {
		sd = ga_get_abs(&gsub->maplevels[i]->subdivs, idx);
		if (sd) {
			if (idx != sd->n)
				log(1, "Error subdiv found as idx:%d real is:%d\n",
					idx, sd->n);
			log(19, "Found in level %d\n", i);
			return sd;
		}
	}

	return NULL;
}
