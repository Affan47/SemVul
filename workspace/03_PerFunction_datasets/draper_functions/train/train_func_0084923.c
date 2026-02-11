allCurrencyCodesList( CurrencyStatusFlags currencyStatus )
{
    QStringList currencyCodes;

    const QStringList paths = KGlobal::dirs()->findAllResources( "locale", QLatin1String("currency/*.desktop") );

    foreach( const QString &path, paths )
    {
        QString code = path.mid( path.length()-11, 3 ).toUpper();

        if ( KCurrencyCode::isValid( code, currencyStatus ) ) {
            currencyCodes.append( code );
        }
    }

    return currencyCodes;
}
