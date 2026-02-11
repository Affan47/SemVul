contributors() const
{
    QStringList res;
    QList<StatementPtr> list = resource()->properties(DublinCoreVocab::self()->contributor());
    QList<StatementPtr>::ConstIterator it = list.constBegin();
    QList<StatementPtr>::ConstIterator end = list.constEnd();
    for ( ; it != end; ++it)
    {
        QString str = (*it)->asString();
        if (!str.isNull())
            res.append(str);
    }
    return res;
}
