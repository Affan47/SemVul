toolbarNameChanged()
{
	LookFeelToolbarsUI *d = (LookFeelToolbarsUI *)w;
	if (!d->cb_toolbars->count())
		return;

	QString name = d->le_toolbarName->text();

	int n = d->cb_toolbars->currentIndex();
	QString base = d->cb_toolbars->itemData(n).toString();
	p->toolbars[base].name = name;

	d->cb_toolbars->setItemText(d->cb_toolbars->findData(base), name);

	emit dataChanged();
}
