date( const QString &text, QDate &d ) const
{

    QDate tmp = KGlobal::locale()->readDate( text );
    if ( KGlobal::locale()->calendar()->isValid( tmp ) ) {
        d = tmp;
        return Acceptable;
    } else {
        return QValidator::Intermediate;
    }
}
