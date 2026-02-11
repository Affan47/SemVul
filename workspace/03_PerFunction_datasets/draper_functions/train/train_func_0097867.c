parseIdString(const QString& idString, QString* managerName, QMap<QString, QString>* params, QString* engineIdString)
{
    QStringList colonSplit = idString.split(QLatin1Char(':'));

    QString prefix = colonSplit.value(0);
    if (prefix != QLatin1String("qtorganizer") || colonSplit.size() != 4)
        return false;

    QString mgrName = colonSplit.value(1);
    QString paramString = colonSplit.value(2);
    QString engIdString = colonSplit.value(3);


    QMap<QString, QString> outParams;
    if (!paramString.isEmpty()) {
        QStringList params = paramString.split(QRegExp(QLatin1String("&(?!(amp;|equ;))")), QString::KeepEmptyParts);


        for(int i = 0; i < params.count(); i++) {

            QStringList paramChunk = params.value(i).split(QLatin1String("="), QString::KeepEmptyParts);

            if (paramChunk.count() != 2)
                return false;

            QString arg = paramChunk.value(0);
            QString param = paramChunk.value(1);

            arg.replace(QLatin1String("&#58;"), QLatin1String(":"));
            arg.replace(QLatin1String("&equ;"), QLatin1String("="));
            arg.replace(QLatin1String("&amp;"), QLatin1String("&"));
            param.replace(QLatin1String("&#58;"), QLatin1String(":"));
            param.replace(QLatin1String("&equ;"), QLatin1String("="));
            param.replace(QLatin1String("&amp;"), QLatin1String("&"));
            if (arg.isEmpty())
                return false;
            outParams.insert(arg, param);
        }
    }


    engIdString.replace(QLatin1String("&#58;"), QLatin1String(":"));
    engIdString.replace(QLatin1String("&amp;"), QLatin1String("&"));


    if (managerName)
        *managerName = mgrName;
    if (params)
        *params = outParams;
    if (engineIdString)
        *engineIdString = engIdString;


    return true;
}
