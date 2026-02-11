gee_tree_set_node_new (gpointer node, GeeTreeSetNode* prev, GeeTreeSetNode* next) {
	GeeTreeSetNode* self;
	gpointer _tmp0_ = NULL;
	GeeTreeSetNode* _tmp1_ = NULL;
	GeeTreeSetNode* _tmp2_ = NULL;
	GeeTreeSetNode* _tmp3_ = NULL;
	GeeTreeSetNode* _tmp5_ = NULL;
	self = g_slice_new0 (GeeTreeSetNode);
	gee_tree_set_node_instance_init (self);
	_tmp0_ = node;
	node = NULL;
	self->key = _tmp0_;
	self->color = GEE_TREE_SET_NODE_COLOR_RED;
	_tmp1_ = prev;
	self->prev = _tmp1_;
	_tmp2_ = next;
	self->next = _tmp2_;
	_tmp3_ = prev;
	if (_tmp3_ != NULL) {
		GeeTreeSetNode* _tmp4_ = NULL;
		_tmp4_ = prev;
		_tmp4_->next = self;
	}
	_tmp5_ = next;
	if (_tmp5_ != NULL) {
		GeeTreeSetNode* _tmp6_ = NULL;
		_tmp6_ = next;
		_tmp6_->prev = self;
	}
	return self;
}
