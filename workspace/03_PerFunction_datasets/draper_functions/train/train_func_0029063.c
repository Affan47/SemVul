GetNextRawFeature()

{


    if( iNextShapeId == 0 && hResultSet == NULL )
    {
        CPLAssert( pszQueryStatement != NULL );

        poDS->RequestLongResult( this );

        if( mysql_query( poDS->GetConn(), pszQueryStatement ) )
        {
            poDS->ReportError( pszQueryStatement );
            return NULL;
        }

        hResultSet = mysql_use_result( poDS->GetConn() );
        if( hResultSet == NULL )
        {
            poDS->ReportError( "mysql_use_result() failed on query." );
            return FALSE;
        }
    }


    char **papszRow;
    unsigned long *panLengths;

    papszRow = mysql_fetch_row( hResultSet );
    if( papszRow == NULL )
    {
        ResetReading();
        return NULL;
    }

    panLengths = mysql_fetch_lengths( hResultSet );


    OGRFeature *poFeature = RecordToFeature( papszRow, panLengths );

    iNextShapeId++;

    return poFeature;
}
