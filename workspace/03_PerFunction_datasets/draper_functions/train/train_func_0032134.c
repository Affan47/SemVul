currentRangeBegin( const QDateTime& datetime ) const
{
    QDateTime result = datetime;
    switch( d->range )
    {
    case Second:
        break;
    case Minute:

        result.setTime( QTime( result.time().hour(), result.time().minute() ) );
        break;
    case Hour:

        result.setTime( QTime( result.time().hour(), 0 ) );
        break;
    case Day:

        result.setTime( QTime( 0, 0 ) );
        break;
    case Week:

        result.setTime( QTime( 0, 0 ) );

        {
            const int weekNumber = result.date().weekNumber();
            while( weekNumber == result.date().addDays( -1 ).weekNumber() )
                result = result.addDays( -1 );
        }
        break;
    case Month:

        result.setTime( QTime( 0, 0 ) );

        result.setDate( QDate( result.date().year(), result.date().month(), 1 ) );
        break;
    case Year:

        result.setTime( QTime( 0, 0 ) );

        result.setDate( QDate( result.date().year(), 1, 1 ) );
        break;
    }
    return result;
}
