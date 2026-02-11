gee_hazard_pointer_node_free (GeeHazardPointerNode* self) {
	GeeHazardPointerNode* _tmp0_ = NULL;
	_tmp0_ = self->_next;
	gee_hazard_pointer_node_free (_tmp0_);
	g_slice_free (GeeHazardPointerNode, self);
}
