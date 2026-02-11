createApplet( int contextId, int appletId,
                             const QString & name, const QString & clazzName,
                             const QString & baseURL, const QString & user,
                             const QString & password, const QString & authname,
                             const QString & codeBase, const QString & jarFile,
                             QSize size, const QMap<QString,QString>& params,
                             const QString & windowTitle )
{


    if ( d->javaProcessFailed ) return false;

    QStringList args;
    args.append( QString::number( contextId ) );
    args.append( QString::number( appletId ) );


    args.append( name );
    args.append( clazzName );
    args.append( baseURL );
    args.append( user );
    args.append( password );
    args.append( authname );
    args.append( codeBase );
    args.append( jarFile );

    args.append( QString::number( size.width() ) );
    args.append( QString::number( size.height() ) );

    args.append( windowTitle );


    const int num = params.count();
    const QString num_params = QString("%1").arg( num, 8 );
    args.append( num_params );

    QMap< QString, QString >::ConstIterator it = params.begin();
    const QMap< QString, QString >::ConstIterator itEnd = params.end();

    for( ; it != itEnd; ++it )
    {
        args.append( it.key() );
        args.append( it.value() );
    }

    process->send( KJAS_CREATE_APPLET, args );

    return true;
}
