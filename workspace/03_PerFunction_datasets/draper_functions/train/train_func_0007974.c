createDate() const
{
    if( d->m_data.created > 0 )
        return QDateTime::fromTime_t(d->m_data.created);
    else
        return QDateTime();
}
