on_cell_TreeView_pseudoAxes_is_initialized_toggled(Glib::ustring const & spath)
{
	LOG;

	Gtk::TreePath path(spath);
	Gtk::TreeModel::iterator iter = _pseudoAxeModel->get_iter(path);
	Gtk::ListStore::Row row = *(iter);
	HklPseudoAxis *pseudoAxis = row[_pseudoAxeModelColumns.pseudoAxis];
	bool old_flag = row[_pseudoAxeModelColumns.is_initialized];
	if (!old_flag){
		int res;

		res = hkl_pseudo_axis_engine_initialize(pseudoAxis->engine, NULL);
		if(res == HKL_SUCCESS)
			this->updatePseudoAxes();
	}
}
