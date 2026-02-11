contacts_row_real_get_preferred_width (GtkWidget* base, gint* minimum_width, gint* natural_width) {
	ContactsRow * self;
	gint _vala_minimum_width = 0;
	gint _vala_natural_width = 0;
	ContactsRowGroup* _tmp0_ = NULL;
	gint _tmp1_ = 0;
	gint _tmp2_ = 0;
	self = (ContactsRow*) base;
	_tmp0_ = self->priv->group;
	contacts_row_group_get_width (_tmp0_, &_tmp1_, &_tmp2_);
	_vala_minimum_width = _tmp1_;
	_vala_natural_width = _tmp2_;
	if (minimum_width) {
		*minimum_width = _vala_minimum_width;
	}
	if (natural_width) {
		*natural_width = _vala_natural_width;
	}
}
