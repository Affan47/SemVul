executeQuery(QSqlQuery *query, const QString &statement, const QList<QVariant> &bindValues)
{
    Q_ASSERT(query != NULL);

    bool success = false;
    enum {Prepare =0 , Execute=1};
    for(int stage=Prepare; stage <= Execute; ++stage) {
        if ( stage == Prepare)
            success = query->prepare(statement);
        else
            success = query->exec();

        if (!success) {
            QString errorText;
            errorText = "Problem: Could not %1 statement: %2"
                "Reason: %3"
                "Parameters: %4\n";
            QString parameters;
            if (bindValues.count() > 0) {
                for(int i = 0; i < bindValues.count(); ++i) {
                    parameters.append(QString("\n\t[") + QString::number(i) + "]: " + bindValues.at(i).toString());
                }
            } else {
                parameters = "None";
            }

            DBError::ErrorCode errorType;
            int result = query->lastError().number();
            if (result == 26 || result == 11) {
                qWarning() << "Service Framework:- Database file is corrupt or invalid:" << databasePath();
                errorType = DBError::InvalidDatabaseFile;
            }
            else if ( result == 8)
                errorType = DBError::NoWritePermissions;
            else
                errorType = DBError::SqlError;

            m_lastError.setError(errorType,
                    errorText
                    .arg(stage == Prepare ?"prepare":"execute")
                    .arg(statement)
                    .arg(query->lastError().text())
                    .arg(parameters));

            query->finish();
            query->clear();
            return false;
        }

        if (stage == Prepare) {
            foreach(const QVariant &bindValue, bindValues)
            query->addBindValue(bindValue);
        }
    }

    m_lastError.setError(DBError::NoError);
    return true;
}
