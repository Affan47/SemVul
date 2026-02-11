promptFilter()
{

	TextFilterDialog dlg(proxy()->filterRegExp());


	KeyValuePairs pairs;
	for (int i = 0; i < locationModel()->columnCount(); i++) {
		QString colName = locationModel()->headerData(i, Qt::Horizontal,
		                                              Qt::DisplayRole)
		                                             .toString();
		pairs[colName] = i;
	}
	dlg.setFilterByList(pairs);
	dlg.setFilterByValue(menuIndex_.column());


	if (dlg.exec() != QDialog::Accepted)
		return;


	proxy()->setFilterKeyColumn(dlg.filterByValue().toInt());
	QRegExp filter = dlg.filter();
	proxy()->setFilterRegExp(filter);
	emit isFiltered(filter.isEmpty());
}
