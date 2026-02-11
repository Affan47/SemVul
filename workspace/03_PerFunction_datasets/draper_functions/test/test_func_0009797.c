boxes_mini_graph_set_ymax (BoxesMiniGraph* self, gdouble value) {
	gdouble _tmp0_ = 0.0;
#line 15 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	g_return_if_fail (self != NULL);
#line 16 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	_tmp0_ = value;
#line 16 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	self->priv->_ymax = _tmp0_;
#line 17 "/extra-data/checkout/gnome/gnome-boxes/src/mini-graph.vala"
	self->priv->ymax_set = TRUE;
#line 767 "mini-graph.c"
}
