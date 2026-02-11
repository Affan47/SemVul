nextAddress( const QString & address )
{
    return parentAddress(address) + QLatin1Char('/') +
        QString::number(positionInParent(address)+1);
}
