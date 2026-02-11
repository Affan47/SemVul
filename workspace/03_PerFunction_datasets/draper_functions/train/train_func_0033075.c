slotData( KIO::Job*, const QByteArray& qb )
{


    KJavaAppletServer* server = KJavaAppletServer::allocateJavaServer();
    if (d->isfirstdata) {
        QString headers = d->job->queryMetaData("HTTP-Headers");
        if (!headers.isEmpty()) {
            d->file.resize( headers.length() );
            memcpy( d->file.data(), headers.toLatin1().constData(), headers.length() );
            server->sendURLData( d->loaderID, HEADERS, d->file );
            d->file.resize( 0 );
        }
        d->isfirstdata = false;
    }
    if ( qb.size() )
        server->sendURLData( d->loaderID, DATA, qb );
    KJavaAppletServer::freeJavaServer();
}
