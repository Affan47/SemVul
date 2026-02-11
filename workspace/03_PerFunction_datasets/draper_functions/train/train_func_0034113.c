setMethod(Method method)
{
    if (method==d->m_Method)
        return;
    beginResetModel();
    if (method==Distribute) {
        d->m_DailySchemes.clear();
    }
    d->m_Method = method;
    d->dailySum();
    Q_EMIT methodChanged();
    endResetModel();
}
