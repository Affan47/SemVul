__lambda26_ (Block31Data* _data31_, gint nr_contacts_marked) {
	ContactsListPane * self;
	gint _tmp0_ = 0;
	gint _tmp1_ = 0;
	self = _data31_->self;
	_tmp0_ = nr_contacts_marked;
	if (_tmp0_ > 0) {
		gtk_widget_set_sensitive ((GtkWidget*) _data31_->delete_selected_button, TRUE);
	} else {
		gtk_widget_set_sensitive ((GtkWidget*) _data31_->delete_selected_button, FALSE);
	}
	_tmp1_ = nr_contacts_marked;
	if (_tmp1_ > 1) {
		gtk_widget_set_sensitive ((GtkWidget*) _data31_->link_selected_button, TRUE);
	} else {
		gtk_widget_set_sensitive ((GtkWidget*) _data31_->link_selected_button, FALSE);
	}
}
