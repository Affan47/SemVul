actionToolTip( const QString& action)
{
	QAction *tmp_Action = m_MainWindow->actionCollection()->action(action);
	if (tmp_Action)
	{
		return tmp_Action->toolTip().toUtf8();
	}
	else
		return "Error no such object!";
}
