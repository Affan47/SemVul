ResetReading()

{
    iNextShapeId = 0;

    if( hResultSet != NULL )
    {
        mysql_free_result( hResultSet );
        hResultSet = NULL;

        poDS->InterruptLongResult();
    }
}
