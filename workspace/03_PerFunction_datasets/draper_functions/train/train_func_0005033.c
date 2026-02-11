CreateFromURL( const char* URL )
{
  std::string urlstr( URL ? URL : "" );
  std::string protocol;
  std::string username;
  std::string unused;
  std::string hostname;
  std::string dataport;
  std::string database;
  std::string dataglom;
  vtkSQLDatabase* db = 0;

  static vtkSimpleCriticalSection dbURLCritSec;
  dbURLCritSec.Lock();


  if ( ! vtksys::SystemTools::ParseURLProtocol( urlstr, protocol, dataglom ))
    {
    vtkGenericWarningMacro( "Invalid URL (no protocol found): \"" << urlstr.c_str() << "\"" );
    dbURLCritSec.Unlock();
    return 0;
    }
  if ( protocol == "sqlite" )
    {
    db = vtkSQLiteDatabase::New();
    db->ParseURL( URL );
    dbURLCritSec.Unlock();
    return db;
    }


  if ( ! vtksys::SystemTools::ParseURL( urlstr, protocol, username,
                                        unused, hostname, dataport, database) )
    {
    vtkGenericWarningMacro( "Invalid URL (other components missing): \"" << urlstr.c_str() << "\"" );
    dbURLCritSec.Unlock();
    return 0;
    }

#ifdef VTK_USE_POSTGRES
  if ( protocol == "psql" )
    {
    db = vtkPostgreSQLDatabase::New();
    db->ParseURL( URL );
    }
#endif

#ifdef VTK_USE_MYSQL
  if ( protocol == "mysql" )
    {
    db = vtkMySQLDatabase::New();
    db->ParseURL( URL );
    }
#endif

#ifdef VTK_USE_ODBC
  if ( protocol == "odbc" )
    {
    db = vtkODBCDatabase::New();
    db->ParseURL( URL );
    }
#endif


  if (!db && vtkSQLDatabase::Callbacks)
    {
    db = vtkSQLDatabase::Callbacks->CreateFromURL( URL );
    }

  if ( ! db )
    {
    vtkGenericWarningMacro( "Unsupported protocol: " << protocol.c_str() );
    }
  dbURLCritSec.Unlock();
  return db;
}
