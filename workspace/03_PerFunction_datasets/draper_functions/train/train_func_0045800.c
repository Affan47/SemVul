receiveList()
{
	GetPrivacyListTask *t = ( GetPrivacyListTask* ) sender();
	if ( !t ) {
		kDebug() << "Unexpected sender.";
		return;
	}

	if ( t->success() ) {
		emit listReceived ( t->list() );
	}
	else {
		kDebug() << "Error in list receiving.";
		emit listError();
	}
}
