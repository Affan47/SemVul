posFromDate( const QDate &date )
{
    int initialPosition = calendar()->day( date );
    int offset = ( d->m_weekDayFirstOfMonth - calendar()->weekStartDay() + d->m_numDayColumns ) % d->m_numDayColumns;


    if ( offset < 1 ) {
        offset += d->m_numDayColumns;
    }

    return initialPosition + offset;
}
