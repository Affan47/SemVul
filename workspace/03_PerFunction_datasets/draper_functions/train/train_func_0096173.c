on_toolbutton_add_crystal_clicked(void)
{
	LOG;

	HklSample *sample = hkl_sample_new("new_sample", HKL_SAMPLE_TYPE_MONOCRYSTAL);
	if(sample){
		hkl_sample_list_append(_samples, sample);
		hkl_sample_list_select_current(_samples, "new_sample");
		this->updateTreeViewCrystals();


		Gtk::TreeModel::Path path;
		Gtk::TreeView::Column * column;
		_treeViewCrystals->get_cursor(path, column);
		column = _treeViewCrystals->get_column(0);
		_treeViewCrystals->set_cursor(path, *column, true);
	}
}
