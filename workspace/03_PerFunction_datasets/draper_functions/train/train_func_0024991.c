updateAxes(void)
{
	LOG;


	Gtk::TreeModel::Children rows = _axeModel->children();
	Gtk::TreeModel::Children::iterator iter = rows.begin();
	Gtk::TreeModel::Children::iterator end = rows.end();
	while(iter != end){
		double min;
		double max;
		HklAxis * axis;

		Gtk::TreeRow row = *iter;
		axis = row[_axeModelColumns.axis];
		row[_axeModelColumns.read] = hkl_axis_get_value_unit(axis);
		row[_axeModelColumns.write] = hkl_axis_get_value_unit(axis);
		hkl_parameter_get_range_unit((HklParameter *)axis, &min, &max);
		row[_axeModelColumns.min] = min;
		row[_axeModelColumns.max] = max;
		++iter;
	}
}
