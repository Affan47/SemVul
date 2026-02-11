gee_hazard_pointer_node_set (GeeHazardPointerNode* self, void* ptr) {
	void* _tmp0_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = ptr;
	g_atomic_pointer_set ((volatile gpointer *) (&self->_hazard), _tmp0_);
}
