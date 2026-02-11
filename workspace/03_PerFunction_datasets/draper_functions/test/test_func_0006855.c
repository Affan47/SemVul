updateCalendar( const DateRange& range )
{
    m_calendar->setDateTextFormat( QDate(), QTextCharFormat() );
    if ( range.start().isValid() )
        m_calendar->setSelectedDate( range.start() );
    else if ( range.end().isValid() )
        m_calendar->setSelectedDate( range.end() );
    else
        m_calendar->setSelectedDate( QDate::currentDate() );
    if ( range.isValid() ) {
        QTextCharFormat selectedFormat;
        selectedFormat.setBackground( q->palette().color( QPalette::Highlight ) );
        selectedFormat.setForeground( q->palette().color( QPalette::HighlightedText ) );
        for ( QDate date = range.start(); date <= range.end(); date = date.addDays( 1 ) ) {
            m_calendar->setDateTextFormat( date, selectedFormat );
        }
    }
}
