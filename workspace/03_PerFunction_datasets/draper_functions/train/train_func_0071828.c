boxes_mini_graph_set_points (BoxesMiniGraph* self, gdouble* value, int value_length1) {
	gdouble* _tmp0_ = NULL;
	gint _tmp0__length1 = 0;
	gdouble* _tmp1_ = NULL;
	gint _tmp1__length1 = 0;
#line 6 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	g_return_if_fail (self != NULL);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	_tmp0_ = value;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	_tmp0__length1 = value_length1;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	_tmp1_ = (_tmp0_ != NULL) ? _vala_array_dup2 (_tmp0_, _tmp0__length1) : ((gpointer) _tmp0_);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	_tmp1__length1 = _tmp0__length1;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	self->priv->_points = (g_free (self->priv->_points), NULL);
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	self->priv->_points = _tmp1_;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	self->priv->_points_length1 = _tmp1__length1;
#line 7 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	self->priv->__points_size_ = self->priv->_points_length1;
#line 8 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	gtk_widget_queue_draw ((GtkWidget*) self);
#line 709 "mini-graph.c"
}
