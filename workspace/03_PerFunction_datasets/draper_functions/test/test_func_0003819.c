initialize()
{
    if (m_initialized)
        return true;


    if (commandLine()->value(Core::ICommandLine::ClearUserDatabases).toBool()) {
        createConnection(USER_DB_CONNECTION, USER_DB_CONNECTION,
                         settings()->databaseConnector(),
                         Utils::Database::DeleteAndRecreateDatabase);
    } else {
        createConnection(USER_DB_CONNECTION, USER_DB_CONNECTION,
                         settings()->databaseConnector(),
                         Utils::Database::CreateDatabase);
    }

    if (!database().isOpen()) {
        if (!database().open()) {
            LOG_ERROR(tkTr(Trans::Constants::UNABLE_TO_OPEN_DATABASE_1_ERROR_2).arg(USER_DB_CONNECTION).arg(database().lastError().text()));
        } else {
            LOG(tkTr(Trans::Constants::CONNECTED_TO_DATABASE_1_DRIVER_2).arg(database().connectionName()).arg(database().driverName() + "@" + database().databaseName()));
        }
    } else {
        LOG(tkTr(Trans::Constants::CONNECTED_TO_DATABASE_1_DRIVER_2).arg(database().connectionName()).arg(database().driverName() + "@" + database().databaseName()));
    }

    if (!checkDatabaseScheme()) {
        LOG_ERROR(tkTr(Trans::Constants::DATABASE_1_SCHEMA_ERROR).arg(USER_DB_CONNECTION));
        return false;
    }

    if (!checkDatabaseVersion())
        return false;


    m_initialized = true;
    return true;
}
