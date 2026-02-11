updateList(const QString& selected)
{
	m_sessions_menu->clear();
	m_sessions_list->clear();

	QStringList files = QDir(Session::path(), "*.session").entryList(QDir::Files, QDir::Name | QDir::IgnoreCase);
	files.prepend(Session::tr("Default"));
	for (int i = 0; i < files.count(); ++i) {
		QString name = Session::pathToName(files.at(i));
		if ((name == Session::tr("Default")) && (i > 0)) {
			continue;
		}

		QAction* action = m_sessions_menu->addAction(fontMetrics().elidedText(name, Qt::ElideRight, 3 * logicalDpiX()));
		action->setData(name);
		action->setCheckable(true);
		m_sessions_actions->addAction(action);
		QListWidgetItem* item = new QListWidgetItem(QIcon::fromTheme("folder"), name, m_sessions_list);
		item->setData(Qt::UserRole, name);

		if (name == m_session->name()) {
			action->setChecked(true);
			item->setIcon(QIcon::fromTheme("folder-open"));
		}

		if (name == selected) {
			m_sessions_list->setCurrentItem(item);
			m_sessions_list->scrollToItem(item);
		}
	}

	m_sessions_menu->addSeparator();
	m_sessions_menu->addAction(QIcon::fromTheme("window-new"), tr("&New..."), this, SLOT(newSession()), tr("Ctrl+Shift+N"));
	m_sessions_menu->addAction(QIcon::fromTheme("view-choose"), tr("&Manage..."), this, SLOT(exec()), tr("Ctrl+Shift+M"));
}
