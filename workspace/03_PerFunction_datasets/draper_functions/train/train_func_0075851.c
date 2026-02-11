find_first_leaf(struct dinode *inoptr,
		    xtpage_t ** addr_leaf_ptr,
		    int64_t * leaf_agg_offset,
		    int8_t * is_inline, int8_t * is_rootleaf)
{
	int ffl_rc = FSCK_OK;
	xtpage_t *xtpg_ptr;
	xad_t *xad_ptr;
	int64_t first_child_addr = 0;

	*is_rootleaf = 0;
	*is_inline = 0;
	*addr_leaf_ptr = NULL;
	*leaf_agg_offset = 0;
	xtpg_ptr = (xtpage_t *) & (inoptr->di_btroot);

	if (xtpg_ptr->header.flag & BT_LEAF) {

		*is_rootleaf = -1;
		*leaf_agg_offset = addressPXD(&(inoptr->di_ixpxd));
	} else {

		while ((ffl_rc == FSCK_OK) && (*addr_leaf_ptr == NULL)) {
			if (xtpg_ptr->header.flag & BT_LEAF) {

				*addr_leaf_ptr = xtpg_ptr;
				*leaf_agg_offset = first_child_addr;
			} else {

				xad_ptr = &(xtpg_ptr->xad[XTENTRYSTART]);
				first_child_addr = addressXAD(xad_ptr);
				ffl_rc = node_get(first_child_addr, &xtpg_ptr);
			}
		}
	}

	return (ffl_rc);
}
