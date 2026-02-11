gee_hash_map_real_clear (GeeAbstractMap* base) {
	GeeHashMap * self;
	self = (GeeHashMap*) base;
	{
		gint i = 0;
		i = 0;
		{
			gboolean _tmp0_ = FALSE;
			_tmp0_ = TRUE;
			while (TRUE) {
				gboolean _tmp1_ = FALSE;
				gint _tmp3_ = 0;
				gint _tmp4_ = 0;
				GeeHashMapNode* node = NULL;
				GeeHashMapNode** _tmp5_ = NULL;
				gint _tmp5__length1 = 0;
				gint _tmp6_ = 0;
				GeeHashMapNode* _tmp7_ = NULL;
				_tmp1_ = _tmp0_;
				if (!_tmp1_) {
					gint _tmp2_ = 0;
					_tmp2_ = i;
					i = _tmp2_ + 1;
				}
				_tmp0_ = FALSE;
				_tmp3_ = i;
				_tmp4_ = self->priv->_array_size;
				if (!(_tmp3_ < _tmp4_)) {
					break;
				}
				_tmp5_ = self->priv->_nodes;
				_tmp5__length1 = self->priv->_nodes_length1;
				_tmp6_ = i;
				_tmp7_ = _tmp5_[_tmp6_];
				_tmp5_[_tmp6_] = NULL;
				node = _tmp7_;
				while (TRUE) {
					GeeHashMapNode* _tmp8_ = NULL;
					GeeHashMapNode* next = NULL;
					GeeHashMapNode* _tmp9_ = NULL;
					GeeHashMapNode* _tmp10_ = NULL;
					GeeHashMapNode* _tmp11_ = NULL;
					GeeHashMapNode* _tmp12_ = NULL;
					GeeHashMapNode* _tmp13_ = NULL;
					_tmp8_ = node;
					if (!(_tmp8_ != NULL)) {
						break;
					}
					_tmp9_ = node;
					_tmp10_ = _tmp9_->next;
					_tmp9_->next = NULL;
					next = _tmp10_;
					_tmp11_ = node;
					((_tmp11_->key == NULL) || (self->priv->k_destroy_func == NULL)) ? NULL : (_tmp11_->key = (self->priv->k_destroy_func (_tmp11_->key), NULL));
					_tmp11_->key = NULL;
					_tmp12_ = node;
					((_tmp12_->value == NULL) || (self->priv->v_destroy_func == NULL)) ? NULL : (_tmp12_->value = (self->priv->v_destroy_func (_tmp12_->value), NULL));
					_tmp12_->value = NULL;
					_tmp13_ = next;
					next = NULL;
					_gee_hash_map_node_free0 (node);
					node = _tmp13_;
					_gee_hash_map_node_free0 (next);
				}
				_gee_hash_map_node_free0 (node);
			}
		}
	}
	self->priv->_nnodes = 0;
	gee_hash_map_resize (self);
}
