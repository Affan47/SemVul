get_seg_interface(seg_manager_t *self, seg_id_t segid)
{
	mem_obj_t *mobj;
	seg_interface_t *retval;

	if (!sm_check(self, segid))
		return NULL;

	mobj = self->heap[segid];
	retval = (seg_interface_t*)sci_malloc(sizeof(seg_interface_t));
	memcpy(retval, seg_interfaces[mobj->type - 1], sizeof (seg_interface_t));

	if (mobj->type != retval->type_id) {
		fprintf(stderr, "Improper segment interface for %d", mobj->type );
		exit(1);
	}

	retval->segmgr = self;
	retval->mobj = mobj;
	retval->seg_id = segid;

	return retval;
}
