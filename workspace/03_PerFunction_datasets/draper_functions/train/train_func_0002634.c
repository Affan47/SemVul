compareStr( const QString& test,
                                                 const int comparison,
                                                 const QString& target ) const
{
    if ( comparison == CompareStrEquals ) {
        if ( test.compare( target, Qt::CaseInsensitive ) == 0 )
            return 1.0;
    } else if ( comparison == CompareStrStartsWith ) {
        if ( test.startsWith( target, Qt::CaseInsensitive ) )
            return 1.0;
    } else if ( comparison == CompareStrEndsWith ) {
        if ( test.endsWith( target, Qt::CaseInsensitive ) )
            return 1.0;
    } else if ( comparison == CompareStrContains ) {
        if ( test.contains( target, Qt::CaseInsensitive ) )
            return 1.0;
    } else if ( comparison == CompareStrRegExp ) {
        QRegExp rx( target );
        if ( rx.indexIn( test ) >= 0 )
            return 1.0;
    } else {
        return 0.0;
    }
    return 0.0;
}
