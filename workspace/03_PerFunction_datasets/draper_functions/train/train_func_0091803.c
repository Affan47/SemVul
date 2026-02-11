slotUpdatePlayerData(QListWidgetItem* item)
{
 if (!item || !d->mGame) {
	return;
 }

 KPlayer* p = d->mGame->findPlayer(item->text().toInt());

 if (!p) {
	kError(11001) << ": cannot find player";
	return;
 }

 clearPlayerData();

 QString buf;
 buf.sprintf("%p", (void*)p);
 d->mPlayerAddress->setText(1, buf);
 d->mPlayerId->setText(1, QString::number(p->id()));
 d->mPlayerName->setText(1, p->name());
 d->mPlayerGroup->setText(1, p->group());
 d->mPlayerUserId->setText(1, QString::number(p->userId()));
 d->mPlayerMyTurn->setText(1, p->myTurn() ? i18n("True") : i18n("False"));
 d->mPlayerAsyncInput->setText(1, p->asyncInput() ? i18n("True") : i18n("False"));
 buf.sprintf("%p", (void*)p->game());
 d->mPlayerKGameAddress->setText(1, buf);
 d->mPlayerVirtual->setText(1, p->isVirtual() ? i18n("True") : i18n("False"));
 d->mPlayerActive->setText(1, p->isActive() ? i18n("True") : i18n("False"));
 d->mPlayerRtti->setText(1, QString::number(p->rtti()));
 d->mPlayerNetworkPriority->setText(1, QString::number(p->networkPriority()));


 KGamePropertyHandler * handler = p->dataHandler();
 QHashIterator<int, KGamePropertyBase*> it((handler->dict()));
 while (it.hasNext()) {
	it.next();
	QString policy;
	switch (it.value()->policy()) {
		case KGamePropertyBase::PolicyClean:
			policy = i18n("Clean");
			break;
		case KGamePropertyBase::PolicyDirty:
			policy = i18n("Dirty");
			break;
		case KGamePropertyBase::PolicyLocal:
			policy = i18n("Local");
			break;
		case KGamePropertyBase::PolicyUndefined:
		default:
			policy = i18n("Undefined");
			break;
	}
  QStringList items;
  items << handler->propertyName(it.value()->id()) << handler->propertyValue(it.value()) << policy;
	new QTreeWidgetItem(d->mPlayerProperties,items);
 }
}
