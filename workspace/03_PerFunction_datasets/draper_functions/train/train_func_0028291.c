structure_set_model (Structure* self, StructureModel* model) {
	StructureModel* _tmp0_ = NULL;
	StructureModel* _tmp2_ = NULL;
	StructureModel* _tmp3_ = NULL;
	GtkTreeView* _tmp4_ = NULL;
	StructureModel* _tmp5_ = NULL;
	gboolean _tmp6_ = FALSE;
	StructureModel* _tmp7_ = NULL;
	g_return_if_fail (self != NULL);
	_tmp0_ = model;
	if (_tmp0_ != NULL) {
		StructureModel* _tmp1_ = NULL;
		_tmp1_ = model;
		structure_model_set_emit_signals (_tmp1_, TRUE);
	}
	_tmp2_ = model;
	_tmp3_ = _g_object_ref0 (_tmp2_);
	_g_object_unref0 (self->priv->_model);
	self->priv->_model = _tmp3_;
	_tmp4_ = self->priv->_tree_view;
	_tmp5_ = model;
	gtk_tree_view_set_model (_tmp4_, (GtkTreeModel*) _tmp5_);
	_tmp7_ = model;
	if (_tmp7_ != NULL) {
		StructureModel* _tmp8_ = NULL;
		guint _tmp9_ = 0U;
		_tmp8_ = model;
		_tmp9_ = structure_model_get_nb_items (_tmp8_);
		_tmp6_ = _tmp9_ <= ((guint) 2000);
	} else {
		_tmp6_ = FALSE;
	}
	if (_tmp6_) {
		GtkTreeView* _tmp10_ = NULL;
		_tmp10_ = self->priv->_tree_view;
		gtk_tree_view_expand_all (_tmp10_);
	}
	structure_populate_simple_list (self);
}
