g_node_unlink_vala (GNode* self) {
	GNode* result = NULL;
	void* ptr = NULL;
	void* _tmp0_ = NULL;
	g_return_val_if_fail (self != NULL, NULL);
	ptr = self;
	g_node_unlink (self);
	_tmp0_ = ptr;
	ptr = NULL;
	result = (GNode*) _tmp0_;
	return result;
}
