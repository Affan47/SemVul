setupRecentMenu()
{
	QList<QAction*> end_timers;
	QList<QAction*> delay_timers;

	for (int i = 0; i < 2; ++i) {
		QString type = QString::number(i);
		QStringList recent = QSettings().value(QString("Timers/Recent%1").arg(i)).toStringList();
		foreach (const QString& timer, recent) {
			QString time = timer.section(' ', 0, 0);
			QString memo = timer.section(' ', 1).simplified();
			memo.truncate(140);

			QAction* action = new QAction(this);
			action->setData(QStringList() << type << time << memo);
			if (i == 0) {
				time = QTime::fromString(time, Qt::ISODate).toString(tr("+HH:mm:ss")).simplified();
				delay_timers.append(action);
			} else {
				time = QTime::fromString(time, Qt::ISODate).toString(Qt::DefaultLocaleLongDate).simplified();
				end_timers.append(action);
			}
			memo = fontMetrics().elidedText(memo, Qt::ElideRight, 300);
			action->setText(!memo.isEmpty() ? tr("%1 - %2").arg(time).arg(memo) : time);
		}
	}

	m_recent_timers->clear();
	foreach (QAction* action, delay_timers) {
		m_recent_timers->addAction(action);
	}
	m_recent_timers->addSeparator();
	foreach (QAction* action, end_timers) {
		m_recent_timers->addAction(action);
	}

	m_recent_button->setEnabled(!m_recent_timers->isEmpty());
}
