loadAll(const QString & databaseName, bool fullLoad, bool dbExists)
{
    FailurePartMessages.clear();
    FailurePropertyMessages.clear();
    m_fullLoad = fullLoad;
	initParts(dbExists);

	int tries = 0;
    m_keepGoing = true;
	while(!m_swappingEnabled && tries < MAX_CONN_TRIES && m_keepGoing) {
		createConnection(databaseName, fullLoad);
		if(!m_swappingEnabled) {
			deleteConnection();
		}
		tries++;
	}


	if (!m_swappingEnabled) {
        noSwappingMessage();
	}
    else if (FailurePartMessages.count() > 0) {
        QString message = tr("The swapping mechanism is disabled for:\n\n");
        if (FailurePartMessages.count() == 1) {
            message += FailurePartMessages.at(0);
        }
        else if (FailurePartMessages.count() < 6) {
            message += FailurePartMessages.join("\n");
        }
        else {
            for (int i = 0; i < 4; i++) {
                message += FailurePartMessages.at(i);
                message += ("\n");
            }
            message += "\n" + tr("and %1 other parts").arg(FailurePartMessages.count() - 4);
        }
	    FMessageBox::warning(NULL, QObject::tr("Oops!"), message, QMessageBox::Ok);
    }
    else if (FailurePropertyMessages.count() > 0) {
        QString message = tr("The swapping mechanism is disabled for:\n\n");
        if (FailurePropertyMessages.count() == 1) {
            message += FailurePropertyMessages.at(0);
        }
        else if (FailurePropertyMessages.count() < 6) {
            message += FailurePropertyMessages.join("\n");
        }
        else {
            for (int i = 0; i < 4; i++) {
                message += FailurePropertyMessages.at(i);
                message += ("\n");
            }
            message += "\n" + tr("and %1 other properties").arg(FailurePropertyMessages.count() - 4);
        }
	    FMessageBox::warning(NULL, QObject::tr("Oops!"), message, QMessageBox::Ok);
    }
    return m_swappingEnabled;

}
