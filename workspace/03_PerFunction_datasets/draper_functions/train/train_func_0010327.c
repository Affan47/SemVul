doOpen()
{
	QString x = d->cb_proxy->itemData(d->cb_proxy->currentItem()).toString();
	connect(d->m, SIGNAL(settingsChanged()), SLOT(pm_settingsChangedApply()));
	d->m->openDialog(x);
}
