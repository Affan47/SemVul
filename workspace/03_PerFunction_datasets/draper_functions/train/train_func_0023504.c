key_model_real_iter_nth_child (GtkTreeModel* base, GtkTreeIter* iter, GtkTreeIter* parent, gint n) {
	KeyModel * self;
	GtkTreeIter _vala_iter = {0};
	gboolean result = FALSE;
	GtkTreeIter* _tmp0_;
	gint _tmp1_;
	Directory* _tmp2_;
	GList* _tmp3_;
	GList* _tmp4_;
	guint _tmp5_ = 0U;
	Directory* _tmp6_;
	GList* _tmp7_;
	GList* _tmp8_;
	gint _tmp9_;
	gconstpointer _tmp10_ = NULL;
	self = (KeyModel*) base;
	memset (&_vala_iter, 0, sizeof (GtkTreeIter));
	_tmp0_ = parent;
	if (_tmp0_ != NULL) {
		result = FALSE;
		if (iter) {
			*iter = _vala_iter;
		}
		return result;
	}
	_tmp1_ = n;
	_tmp2_ = self->priv->directory;
	_tmp3_ = directory_get_keys (_tmp2_);
	_tmp4_ = _tmp3_;
	_tmp5_ = g_list_length (_tmp4_);
	if (((guint) _tmp1_) >= _tmp5_) {
		result = FALSE;
		if (iter) {
			*iter = _vala_iter;
		}
		return result;
	}
	_tmp6_ = self->priv->directory;
	_tmp7_ = directory_get_keys (_tmp6_);
	_tmp8_ = _tmp7_;
	_tmp9_ = n;
	_tmp10_ = g_list_nth_data (_tmp8_, (guint) _tmp9_);
	key_model_set_iter (self, &_vala_iter, (Key*) _tmp10_);
	result = TRUE;
	if (iter) {
		*iter = _vala_iter;
	}
	return result;
}
