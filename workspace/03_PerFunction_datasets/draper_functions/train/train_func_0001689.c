AddColumnToTable(
  int tblHandle, int colType, const char* colName,
  int colSize, const char* colOpts )
{
  if ( ! colName )
    {
    vtkErrorMacro( "Cannot add column with empty name to table " << tblHandle );
    return -1;
    }

  if ( tblHandle < 0 || tblHandle >= this->GetNumberOfTables() )
    {
    vtkErrorMacro( "Cannot add column to non-existent table " << tblHandle );
    return -1;
    }


  int colHandle = static_cast<int>(this->Internals->Tables[tblHandle].Columns.size());
  this->Internals->Tables[tblHandle].Columns.resize( colHandle + 1 );
  vtkSQLDatabaseSchemaInternals::Column* column = &this->Internals->Tables[tblHandle].Columns[colHandle];
  column->Type = static_cast<DatabaseColumnType>( colType );
  column->Size = colSize;
  column->Name = colName;
  column->Attributes = colOpts;
  return colHandle;
}
