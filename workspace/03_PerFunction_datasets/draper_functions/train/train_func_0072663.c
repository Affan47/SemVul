createAndSendStandingOrder(const widgetTransfer *sender)
{
	const aqb_AccountInfo *acc = sender->localAccount->getAccount();
	abt_transaction *t = new abt_transaction();

	t->fillLocalFromAccount(acc->get_AB_ACCOUNT());


	t->setIdForApplication(QDateTime::currentDateTime().toTime_t());

	t->setRemoteAccountNumber(sender->remoteAccount->getAccountNumber());
	t->setRemoteName(QStringList(sender->remoteAccount->getName()));
	t->setRemoteBankCode(sender->remoteAccount->getBankCode());
	t->setRemoteBankName(sender->remoteAccount->getBankName());

	t->setValue(sender->value->getValueABV());

	t->setPurpose(sender->purpose->getPurpose());

	t->setTextKey(sender->textKey->getTextKey());

	t->setCycle(sender->recurrence->getCycle());
	t->setPeriod(sender->recurrence->getPeriod());
	t->setExecutionDay(sender->recurrence->getExecutionDay());


	t->setFirstExecutionDate(sender->recurrence->getFirstExecutionDate());
	t->setLastExecutionDate(sender->recurrence->getLastExecutionDate());
	t->setNextExecutionDate(sender->recurrence->getNextExecutionDate());

	this->jobctrl->addCreateStandingOrder(acc, t);

	delete t;
}
