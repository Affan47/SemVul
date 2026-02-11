saveSettings()
{
	QSettings settings;
	settings.setValue("SymbolsDialog/Size", size());
	settings.setValue("SymbolsDialog/SplitterSizes", m_contents->saveState());
	settings.setValue("SymbolsDialog/Group", m_groups->currentIndex());
	QList<QVariant> recent;
	for (int i = 0; i < 16; ++i) {
		QTableWidgetItem* item = m_recent->item(0, i);
		if (item && (item->flags() & Qt::ItemIsEnabled)) {
			recent += item->data(Qt::UserRole);
		}
	}
	settings.setValue("SymbolsDialog/Recent", recent);
	settings.setValue("SymbolsDialog/Current", m_view->currentIndex().internalId());
}
