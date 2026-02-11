prepareQuery(QSqlQuery &bindedQuery) const
{
    bindedQuery.bindValue(DATA_USER_UUID,  d->m_UserUuid);
    bindedQuery.bindValue(DATA_DATANAME ,  d->m_Name);

    if (d->m_Name==Constants::USER_DATA_PREFERENCES) {
        bindedQuery.bindValue(DATA_STRING ,    QVariant());
        bindedQuery.bindValue(DATA_LONGSTRING, QVariant());
        bindedQuery.bindValue(DATA_FILE,       d->m_Value);
        bindedQuery.bindValue(DATA_NUMERIC,    QVariant());
        bindedQuery.bindValue(DATA_DATE,       QVariant());
    } else {
        switch (d->m_Value.type())
        {
        case QVariant::DateTime :
        {
        bindedQuery.bindValue(DATA_STRING ,    QVariant());
        bindedQuery.bindValue(DATA_LONGSTRING, QVariant());
        bindedQuery.bindValue(DATA_FILE,       QVariant());
        bindedQuery.bindValue(DATA_NUMERIC,    QVariant());
        bindedQuery.bindValue(DATA_DATE,       d->m_Value);
            break;
        }
        case QVariant::Double :
        case QVariant::Int :
        {
        bindedQuery.bindValue(DATA_STRING ,    QVariant());
        bindedQuery.bindValue(DATA_LONGSTRING, QVariant());
        bindedQuery.bindValue(DATA_FILE,       QVariant());
        bindedQuery.bindValue(DATA_NUMERIC,    d->m_Value);
        bindedQuery.bindValue(DATA_DATE,       QVariant());
            break;
        }
        default:
        {
            QString tmp = d->m_Value.toString();
            if (type() == ExtraDocument)
                tmp = d->m_Doc->toXml();
            if (tmp.length() < 200) {
        bindedQuery.bindValue(DATA_STRING ,    tmp);
        bindedQuery.bindValue(DATA_LONGSTRING, QVariant());
        bindedQuery.bindValue(DATA_FILE,       QVariant());
            } else if (tmp.length() < 2000) {
        bindedQuery.bindValue(DATA_STRING ,    QVariant());
        bindedQuery.bindValue(DATA_LONGSTRING, tmp);
        bindedQuery.bindValue(DATA_FILE,       QVariant());
            } else {
        bindedQuery.bindValue(DATA_STRING ,    QVariant());
        bindedQuery.bindValue(DATA_LONGSTRING, QVariant());
        bindedQuery.bindValue(DATA_FILE,       tmp);
            }
        bindedQuery.bindValue(DATA_NUMERIC,    QVariant());
        bindedQuery.bindValue(DATA_DATE,       QVariant());
            break;
        }
        }
    }
    bindedQuery.bindValue(DATA_LANGUAGE,   d->m_Language);
    bindedQuery.bindValue(DATA_LASTCHANGE, d->m_Lastchange);
    bindedQuery.bindValue(DATA_TRACE_ID,   d->m_Trace);
}
