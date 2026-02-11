select_nodeinfo_get(select_nodeinfo_t *nodeinfo,
			       enum select_nodedata_type dinfo,
			       enum node_states state,
			       void *data)
{
	int rc = SLURM_SUCCESS;
	uint16_t *uint16 = (uint16_t *) data;
	bitstr_t **bitmap = (bitstr_t **) data;
	char **tmp_char = (char **) data;
	ListIterator itr = NULL;
	node_subgrp_t *subgrp = NULL;

	if (nodeinfo == NULL) {
		error("get_nodeinfo: nodeinfo not set");
		return SLURM_ERROR;
	}

	if (nodeinfo->magic != NODEINFO_MAGIC) {
		error("get_nodeinfo: nodeinfo magic bad");
		return SLURM_ERROR;
	}

	switch (dinfo) {
	case SELECT_NODEDATA_BITMAP_SIZE:
		*uint16 = nodeinfo->bitmap_size;
		break;
	case SELECT_NODEDATA_SUBGRP_SIZE:
		*uint16 = 0;
		if (!nodeinfo->subgrp_list)
			return SLURM_ERROR;
		*uint16 = list_count(nodeinfo->subgrp_list);
		break;
	case SELECT_NODEDATA_SUBCNT:
		*uint16 = 0;
		if (!nodeinfo->subgrp_list)
			return SLURM_ERROR;
		itr = list_iterator_create(nodeinfo->subgrp_list);
		while ((subgrp = list_next(itr))) {
			if (subgrp->state == state) {
				*uint16 = subgrp->cnode_cnt;
				break;
			}
		}
		list_iterator_destroy(itr);
		break;
	case SELECT_NODEDATA_BITMAP:
		*bitmap = NULL;
		if (!nodeinfo->subgrp_list)
			return SLURM_ERROR;
		itr = list_iterator_create(nodeinfo->subgrp_list);
		while ((subgrp = list_next(itr))) {
			if (subgrp->state == state) {
				*bitmap = bit_copy(subgrp->bitmap);
				break;
			}
		}
		list_iterator_destroy(itr);
		break;
	case SELECT_NODEDATA_RACK_MP:
		if (nodeinfo->ba_mp)
			*tmp_char = xstrdup(nodeinfo->ba_mp->loc);
		else if (nodeinfo->rack_mp)
			*tmp_char = xstrdup(nodeinfo->rack_mp);
		break;
	case SELECT_NODEDATA_STR:
		*tmp_char = NULL;
		if (!nodeinfo->subgrp_list)
			return SLURM_ERROR;
		itr = list_iterator_create(nodeinfo->subgrp_list);
		while ((subgrp = list_next(itr))) {
			if (subgrp->state == state) {
				*tmp_char = xstrdup(subgrp->str);
				break;
			}
		}
		list_iterator_destroy(itr);
		break;
	case SELECT_NODEDATA_EXTRA_INFO:
		if (nodeinfo->extra_info)
			*tmp_char = xstrdup(nodeinfo->extra_info);
		if (nodeinfo->failed_cnodes)
			xstrfmtcat(*tmp_char, "Failed cnodes=%s",
				   nodeinfo->failed_cnodes);
		break;
	default:
		error("Unsupported option %d for get_nodeinfo.", dinfo);
		rc = SLURM_ERROR;
		break;
	}
	return rc;
}
