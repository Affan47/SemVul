isDontAsk( const QString op ) const
{
    return QSettings().value( op + "DontAsk" ).toBool();
}
