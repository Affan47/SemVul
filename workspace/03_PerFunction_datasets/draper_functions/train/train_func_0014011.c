initDatabase()
{
    QMutexLocker locker_q( &m_mutex );

    if ( !m_db.isValid() )
    {
        m_db = QSqlDatabase::addDatabase( "QSQLITE", "collection" );

        if ( m_dbPath.isEmpty() )
            m_db.setDatabaseName( UnicornUtils::appDataPath() + "/Last.fm/collection.db" );
        else
            m_db.setDatabaseName( m_dbPath );
    }
    m_db.open();

    qDebug() << "Opening Collection database" << ( m_db.isValid() ? "worked" : "failed" );
    if ( !m_db.isValid() )
        return false;

    if ( !m_db.tables().contains( "files" ) )
    {
        qDebug() << "Creating Collection database!";

        query( "CREATE TABLE artists ("
                    "id          INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "serverUid   INTEGER,"
                    "lcName      TEXT NOT NULL,"
                    "displayName TEXT NOT NULL );" );

        query( "CREATE TABLE albums ("
                    "id            INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "serverUid     INTEGER,"
                    "lcName        TEXT NOT NULL,"
                    "displayName   TEXT NOT NULL,"
                    "primaryArtist INTEGER NOT NULL );" );

        query( "CREATE UNIQUE INDEX album_names_idx ON albums ( primaryArtist, lcName );" );

        query( "CREATE TABLE tracks ("
                    "id                INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "lcName            TEXT NOT NULL,"
                    "displayName       TEXT NOT NULL,"
                    "primaryArtist     INTEGER NOT NULL,"
                    "primaryAlbum      INTEGER );" );

        query( "CREATE UNIQUE INDEX track_names_idx ON tracks ( primaryArtist, lcName );" );

        query( "CREATE TABLE files ("
                    "id                INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "uri               TEXT NOT NULL,"
                    "track             INTEGER NOT NULL,"
                    "bitrate           INTEGER,"
                    "samplerate        INTEGER,"
                    "duration          INTEGER,"
                    "filesize          INTEGER,"
                    "source            INTEGER,"
                    "modificationDate  INTEGER,"
                    "lastPlayDate      INTEGER,"
                    "playCounter       INTEGER,"
                    "mbId              VARCHAR( 36 ),"
                    "fpId              INTEGER );" );

        query( "CREATE UNIQUE INDEX files_uri_idx ON files ( uri );" );
        query( "CREATE INDEX files_track_idx ON files ( track );" );
        query( "CREATE INDEX files_fpId_idx ON files ( fpId );" );
        query( "CREATE INDEX files_source_idx ON files ( source );" );

        query( "CREATE TABLE sources ("
                    "id          INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name        TEXT UNIQUE,"
                    "available   INTEGER,"
                    "host        TEXT,"
                    "cost        INTEGER );" );

        query( "CREATE TABLE genres ("
                    "id          INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "name        TEXT UNIQUE );" );

        query( "CREATE TABLE labels ("
                    "id          INTEGER PRIMARY KEY AUTOINCREMENT,"
                    "serverUid   INTEGER UNIQUE,"
                    "name        TEXT );" );
    }

    int const v = version();
    if ( v < k_collectionDbVersion )
    {
        qDebug() << "Upgrading Collection::db from" << v << "to" << k_collectionDbVersion;


        if ( v < 1 )
        {


            query( "UPDATE files SET fpId = NULL;" );

            query( "CREATE TABLE metadata ("
                        "key         TEXT UNIQUE NOT NULL,"
                        "value       TEXT );" );

            query( "INSERT INTO metadata (key, value) VALUES ('version', '1');" );
        }


        query( "UPDATE metadata set key='version', value='"
                    + QString::number( k_collectionDbVersion ) + "';" );
    }

    return true;
}
