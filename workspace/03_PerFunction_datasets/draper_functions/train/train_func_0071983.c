characters( const QString& ch )
{
    QString t = ch;
    t.replace( "\r", "" );
    accum += t;
    return true;
}
