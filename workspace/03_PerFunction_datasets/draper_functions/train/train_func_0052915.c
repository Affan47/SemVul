infoMessage( QNetworkReply::NetworkError code )
{
    if( code != QNetworkReply::NoError )
    {
        QNetworkReply *reply = qobject_cast<QNetworkReply*>( sender() );
        setDescription( reply->errorString() );
    }
}
