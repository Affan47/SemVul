getDefault_listsReceived ( const QString& defaultList, const QString&, const QStringList& )
{
	disconnect ( this,SIGNAL (listsReceived(QString,QString,QStringList)),this,SLOT (getDefault_listsReceived(QString,QString,QStringList)) );
	disconnect ( this,SIGNAL (listsError()),this,SLOT (getDefault_listsError()) );

	getDefault_default_ = defaultList;
	if ( !defaultList.isEmpty() ) {
		getDefault_waiting_ = true;
		connect ( this,SIGNAL (listReceived(PrivacyList)),SLOT (getDefault_listReceived(PrivacyList)) );
		connect ( this,SIGNAL (listError()),SLOT (getDefault_listError()) );
		requestList ( defaultList );
	}
	else {
		emit defaultListAvailable ( PrivacyList ( "" ) );
	}
}
