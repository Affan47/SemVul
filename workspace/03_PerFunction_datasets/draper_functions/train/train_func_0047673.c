checkTables()
{
    bool bTables(false);
    QStringList tables = QSqlDatabase::database(m_connectionName).tables();
    if (tables.contains(SERVICE_TABLE)
        && tables.contains(INTERFACE_TABLE)
        && tables.contains(DEFAULTS_TABLE)
        && tables.contains(SERVICE_PROPERTY_TABLE)
        && tables.contains(INTERFACE_PROPERTY_TABLE)){
            bTables = true;
    }
    return bTables;
}
