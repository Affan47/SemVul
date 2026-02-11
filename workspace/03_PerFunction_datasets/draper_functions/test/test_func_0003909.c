receiveLists()
{
	GetPrivacyListsTask *t = ( GetPrivacyListsTask* ) sender();
	if ( !t ) {
		kWarning () << "Unexpected sender.";
		return;
	}

	if ( t->success() ) {
		emit listsReceived ( t->defaultList(),t->activeList(),t->lists() );
	}
	else {
		kDebug() << "Error in lists receiving.";
		emit listsError();
	}
}
