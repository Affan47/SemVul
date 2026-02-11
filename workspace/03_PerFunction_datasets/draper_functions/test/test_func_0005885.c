AddTable( const char* tblName )
{
  if ( ! tblName )
    {
    vtkErrorMacro( "Cannot add table with empty name" );
    return -1;
    }

  vtkSQLDatabaseSchemaInternals::Table newTbl;
  int tblHandle = static_cast<int>(this->Internals->Tables.size());
  newTbl.Name = tblName;
  this->Internals->Tables.push_back( newTbl );
  return tblHandle;
}
