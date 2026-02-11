updateMode(void)
{
	size_t i;

	_mode_ListStore->clear();
	for(i=0; i<HKL_LIST_LEN(_engine->modes); ++i){
		Gtk::TreeRow row = *(_mode_ListStore->append());
		row[_mode_columns.name] = _engine->modes[i]->name;
	}
}
