onCoreDatabaseServerChanged()
{
    m_initialized = false;
    if (QSqlDatabase::connectionNames().contains(Constants::DB_NAME)) {
        QSqlDatabase::removeDatabase(Constants::DB_NAME);
    }
    disconnect(Core::ICore::instance(), SIGNAL(databaseServerChanged()), this, SLOT(onCoreDatabaseServerChanged()));
    disconnect(Core::ICore::instance(), SIGNAL(firstRunDatabaseCreation()), this, SLOT(onCoreFirstRunCreationRequested()));
    initialize();
}
