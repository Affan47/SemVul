run()
{
    QDir d( m_cacheDir );
    const QStringList files = d.entryList( QStringList() << "c*", QDir::Files );

    foreach( QString file, files )
    {
        if ( m_abort )
            return;

        QFile f( d.filePath( file ) );
        if ( f.open( QIODevice::ReadOnly ) )
        {
            QByteArray expdate = f.read( 10 );
            f.close();

            bool ok;
            if ( expdate.toUInt( &ok ) < QDateTime::currentDateTime().toTime_t() )
            {
                if ( !ok )
                    qDebug() << "Doesn't seem to be a valid cache file:" << d.filePath( file );

                if ( d.remove( file ) )
                    qDebug() << "Removing from cache:" << d.filePath( file );
                else
                    qDebug() << "Failed removing from cache:" << d.filePath( file );
            }
        }
    }

    deleteLater();
}
