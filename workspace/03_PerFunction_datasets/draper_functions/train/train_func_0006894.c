setToolBarStatusTip(bool enabled)
{
	QAction *action = qobject_cast<QAction*>(sender());
	if (enabled)
		action->setStatusTip(tr("Hide toolbar \"%1\"").arg(action->text()));
	else
		action->setStatusTip(tr("Show toolbar \"%1\"").arg(action->text()));
}
