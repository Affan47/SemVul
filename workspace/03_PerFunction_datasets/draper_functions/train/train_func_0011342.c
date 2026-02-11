slotResult( KJob* )
{
    kDebug(6100) << "slotResult(" << d->loaderID << ")";

    KJavaAppletServer* server = KJavaAppletServer::allocateJavaServer();
    if( d->job->error())
    {
        kDebug(6100) << "slave had an error = " << d->job->errorString();
        int code = d->job->error();
        if (!code)
            code = 404;
        QString codestr = QString::number(code);
        d->file.resize(codestr.length());
        memcpy( d->file.data(), codestr.toLatin1().constData(), codestr.length() );
        kDebug(6100) << "slave had an error = " << code;

        server->sendURLData( d->loaderID, ERRORCODE, d->file );
        d->file.resize( 0 );
    }
    else
    {
        server->sendURLData( d->loaderID, FINISHED, d->file );
    }
    d->job = 0L;
    server->removeDataJob( d->loaderID );
    KJavaAppletServer::freeJavaServer();
}
