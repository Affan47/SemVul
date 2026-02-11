savePath( QString file )
{
    QString path;

    #ifdef WIN32
        path = UnicornUtils::appDataPath();
        if ( path.isEmpty() )
            path = QApplication::applicationDirPath();
        else
            path += "/Last.fm/Client";
    #else
        path = UnicornUtils::appDataPath() + "/Last.fm";
    #endif

    QDir d( path );
    d.mkpath( path );

    return d.filePath( file );
}
