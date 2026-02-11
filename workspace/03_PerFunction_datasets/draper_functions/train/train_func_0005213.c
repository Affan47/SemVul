setLevelset(const QString& levelname)
{
    if( levelname == m_levelname ){
        return;
    }
    m_levelname = levelname;


    QString path = "levelsets/" + m_levelname + ".levelset";
    path =  KStandardDirs::locate("appdata", path);


    delete m_levelset;

    m_levelset = new QDomDocument( m_levelname );
    QFile file( path );
    if( !file.open( QIODevice::ReadOnly ) ){
        kError() << "Can't open file " << path << endl;
    }

    QString errorString;
    int errorLine;
    int errorColumn;
    if( !m_levelset->setContent( &file, false, &errorString, &errorLine, &errorColumn ) ){
        file.close();

        KConfig kconfigfile(path, KConfig::SimpleConfig);
        if( kconfigfile.hasGroup( "level1" ) ){

            m_oldstyle = true;
            kError() << "Warning: Using deprecated KConfig-levelset. Please change to XML-Style.\n";
        } else {
            kError() << "Can't read levelset from " << path << "\nError: " << errorString <<
                        " in Line " << errorLine << ", Column " << errorColumn << endl;
        }
    } else {

        m_oldstyle = false;
    }
    file.close();

}
