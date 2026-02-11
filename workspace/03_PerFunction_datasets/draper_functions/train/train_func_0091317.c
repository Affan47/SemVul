gmpc_widgets_qtable_clear (GmpcWidgetsQtable* self) {
	GList* _tmp0_;
	g_return_if_fail (self != NULL);
	_tmp0_ = self->priv->children;
	{
		GList* a_collection = NULL;
		GList* a_it = NULL;
		a_collection = _tmp0_;
		for (a_it = a_collection; a_it != NULL; a_it = a_it->next) {
			QtableEntry* _tmp1_;
			QtableEntry* a = NULL;
			_tmp1_ = _qtable_entry_ref0 ((QtableEntry*) a_it->data);
			a = _tmp1_;
			{
				QtableEntry* _tmp2_;
				GtkWidget* _tmp3_;
				gint _tmp4_;
				_tmp2_ = a;
				_tmp3_ = _tmp2_->widget;
				gtk_widget_unparent (_tmp3_);
				_tmp4_ = self->priv->num_items;
				self->priv->num_items = _tmp4_ - 1;
				_qtable_entry_unref0 (a);
			}
		}
	}
	__g_list_free__qtable_entry_unref0_0 (self->priv->children);
	self->priv->children = NULL;
	gtk_widget_queue_resize ((GtkWidget*) self);
}
