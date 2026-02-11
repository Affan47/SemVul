default_sort (const Gtk::TreeIter& a, const Gtk::TreeIter& b)
{
	TableListColumns &cols = TableListColumns::get ();
	unsigned int a_number = a->get_value (cols.number),
		b_number = b->get_value (cols.number);

	if (a_number < b_number)
		return -1;
	else if (a_number > b_number)
		return 1;
	else
		return 0;
}
