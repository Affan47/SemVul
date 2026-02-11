ReportError( const char *pszDescription )

{
    if( pszDescription )
        CPLError( CE_Failure, CPLE_AppDefined,
                  "MySQL error message:%s Description: %s",
                  mysql_error( hConn ),
                  pszDescription );
    else
        CPLError( CE_Failure, CPLE_AppDefined,
                  "%s", mysql_error( hConn ) );
}
