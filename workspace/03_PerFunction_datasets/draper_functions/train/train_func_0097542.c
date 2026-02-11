GetTableNameFromType(const char* pszTableType)
{
    CPLODBCStatement oStmt( &oSession );

    oStmt.Appendf( "SELECT TableName FROM GAliasTable WHERE TableType = '%s'", pszTableType );

    if( !oStmt.ExecuteSQL() )
    {
        CPLDebug( "GEOMEDIA",
                  "SELECT for %s on GAliasTable fails, perhaps not a geomedia geodatabase?\n%s",
                  pszTableType,
                  oSession.GetLastError() );
        return "";
    }

    while( oStmt.Fetch() )
    {
        return oStmt.GetColData(0);
    }

    return "";
}
