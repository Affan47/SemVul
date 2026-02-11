gee_linked_list_iterator_real_remove (GeeIterator* base) {
	GeeLinkedListIterator * self;
	gint _tmp0_ = 0;
	GeeLinkedList* _tmp1_ = NULL;
	gint _tmp2_ = 0;
	GeeLinkedListNode* _tmp3_ = NULL;
	GeeLinkedListNode* new_position = NULL;
	GeeLinkedListNode* _tmp4_ = NULL;
	GeeLinkedListNode* _tmp5_ = NULL;
	GeeLinkedListNode* _tmp6_ = NULL;
	GeeLinkedList* _tmp7_ = NULL;
	GeeLinkedListNode* _tmp8_ = NULL;
	GeeLinkedListNode* _tmp9_ = NULL;
	GeeLinkedList* _tmp10_ = NULL;
	gint _tmp11_ = 0;
	self = (GeeLinkedListIterator*) base;
	_tmp0_ = self->priv->_stamp;
	_tmp1_ = self->priv->_list;
	_tmp2_ = _tmp1_->priv->_stamp;
	_vala_assert (_tmp0_ == _tmp2_, "this._stamp == this._list._stamp");
	_tmp3_ = self->priv->position;
	_vala_assert (_tmp3_ != NULL, "this.position != null");
	_tmp4_ = self->priv->position;
	_tmp5_ = _tmp4_->next;
	new_position = _tmp5_;
	_tmp6_ = new_position;
	if (_tmp6_ == NULL) {
		self->priv->started = FALSE;
	}
	_tmp7_ = self->priv->_list;
	_tmp8_ = self->priv->position;
	_gee_linked_list_remove_node (_tmp7_, _tmp8_);
	_tmp9_ = new_position;
	self->priv->position = _tmp9_;
	self->priv->removed = TRUE;
	_tmp10_ = self->priv->_list;
	_tmp11_ = _tmp10_->priv->_stamp;
	self->priv->_stamp = _tmp11_;
}
