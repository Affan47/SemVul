editStyle(const QModelIndex& index)
{
	QModelIndex propRoot = index.child(0, 2);
	propView_->setRootIndex(propRoot);
}
