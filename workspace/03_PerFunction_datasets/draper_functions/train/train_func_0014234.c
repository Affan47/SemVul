updateSolutions(void)
{
	LOG;

	size_t i;

	_solutionModel->clear();
	Gtk::ListStore::Row row;
	for(i=0; i<hkl_geometry_list_len(_engines->geometries); ++i){
		size_t j;
		HklGeometry *geometry;

		geometry = _engines->geometries->items[i]->geometry;

		row = *(_solutionModel->append());
		row[_solutionModelColumns->index] = i;
		for(j=0; j<HKL_LIST_LEN(geometry->axes); ++j)
			row[_solutionModelColumns->axes[j]] =
				hkl_parameter_get_value_unit((HklParameter *)&geometry->axes[j]);
	}
}
