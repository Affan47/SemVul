receiveLists()
{
	GetPrivacyListsTask *t = (GetPrivacyListsTask*)sender();
	if (!t) {
		qWarning("privacy.cpp:receiveLists(): Unexpected sender.");
		return;
	}

	if (t->success()) {
		emit listsReceived(t->defaultList(),t->activeList(),t->lists());
	}
	else {
		qDebug("privacy.cpp: Error in lists receiving.");
		emit listsError();
	}
}
