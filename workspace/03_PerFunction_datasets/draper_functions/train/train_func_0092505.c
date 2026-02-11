createJobInfoStringList_Append_To_Sepa(QStringList *strList) const
{
	if (!this->m_trans) return;
	QString info;

	info = QObject::tr("Zu:  %1 (%2 - %3)").arg(this->m_trans->getRemoteName().at(0),
						    this->m_trans->getRemoteIban(),
						    this->m_trans->getRemoteBic());
	strList->append(info);
}
