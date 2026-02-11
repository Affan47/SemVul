createJobInfoStringList_EuTransfer(QStringList *strList) const
{
	this->createJobInfoStringList_Append_From(strList);
	strList->append(QObject::tr("Zu:  %1 (%2 - %3) [%4]").arg(
			this->m_trans->getRemoteName().at(0),
			this->m_trans->getRemoteAccountNumber(),
			this->m_trans->getRemoteBankCode(),
			this->m_trans->getRemoteBankLocation()));
	this->createJobInfoStringList_Append_Purpose(strList);
	this->createJobInfoStringList_Append_Value(strList);
}
