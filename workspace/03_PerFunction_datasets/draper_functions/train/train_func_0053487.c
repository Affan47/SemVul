prepareToSave()
{
    if( m_verbose )
        qDebug() << "prepareToSave start";
    m_cleanupNeeded = true;
    QCryptographicHash md5sum( QCryptographicHash::Md5 );

    QString pid;
#ifdef Q_WS_WIN
    pid.setNum( _getpid() );
#else
    pid.setNum( getpid() );
#endif

    int length = 8;

    QString str; str.resize( length );
    int i = 0;
    while( length-- )
    {
        int r = qrand() % 62;
        r+=48;
        if( r > 57 ) r+=7;
        if( r > 90 ) r+=6;
        str[i++] = char( r );
    }

    QString randomString = str;

    m_tempSavePath = m_origPath + '.' + m_prefix + "temp.pid-" + pid + ".random-" + randomString + '.' + QFileInfo( m_origPath ).suffix();
    m_origRenamedSavePath = m_origPath + '.' + m_prefix + "original.pid-" + pid + ".random-" + randomString + '.' + QFileInfo( m_origPath ).suffix();


    if( m_verbose )
        qDebug() << "Copying original file " << m_origPath << " to copy at " << m_tempSavePath << " and caluclating MD5";

    if( !QFile::copy( m_origPath, m_tempSavePath ) )
    {
        if( m_verbose )
            qDebug() << "Could not copy the file.  Check that you have sufficient permissions/disk space "
                   "and that the destination path does not already exist!";
        return QString();
    }

    QFile tempFile( m_tempSavePath );
    if( !tempFile.open( QIODevice::ReadOnly | QIODevice::Unbuffered ) )
    {
        if( m_verbose )
            qDebug() << "Could not open temp file for MD5 calculation!";
        return QString();
    }

    md5sum.addData( tempFile.readLine() );
    m_tempSaveDigest = md5sum.result().toHex();

    tempFile.close();


    if( m_verbose )
        qDebug() << "MD5 sum of temp file: " << m_tempSaveDigest;


    return m_tempSavePath;
}
