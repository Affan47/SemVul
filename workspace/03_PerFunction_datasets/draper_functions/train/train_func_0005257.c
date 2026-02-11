comp_data_refs(struct btrfs_delayed_data_ref *ref2,
			  struct btrfs_delayed_data_ref *ref1)
{
	if (ref1->node.type == BTRFS_EXTENT_DATA_REF_KEY) {
		if (ref1->root < ref2->root)
			return -1;
		if (ref1->root > ref2->root)
			return 1;
		if (ref1->objectid < ref2->objectid)
			return -1;
		if (ref1->objectid > ref2->objectid)
			return 1;
		if (ref1->offset < ref2->offset)
			return -1;
		if (ref1->offset > ref2->offset)
			return 1;
	} else {
		if (ref1->parent < ref2->parent)
			return -1;
		if (ref1->parent > ref2->parent)
			return 1;
	}
	return 0;
}
