ReorderFields( int* panMap )
{
    if (HasLayerDefnError())
        return OGRERR_FAILURE;

    if (!poDS->GetUpdate())
    {
        CPLError( CE_Failure, CPLE_NotSupported,
                  UNSUPPORTED_OP_READ_ONLY,
                  "ReorderFields");
        return OGRERR_FAILURE;
    }

    if (poFeatureDefn->GetFieldCount() == 0)
        return OGRERR_NONE;

    OGRErr eErr = OGRCheckPermutation(panMap, poFeatureDefn->GetFieldCount());
    if (eErr != OGRERR_NONE)
        return eErr;

    ClearInsertStmt();
    ResetReading();


    int iField;
    char *pszNewFieldList, *pszFieldListForSelect;
    InitFieldListForRecrerate(pszNewFieldList, pszFieldListForSelect);

    for( iField = 0; iField < poFeatureDefn->GetFieldCount(); iField++ )
    {
        OGRFieldDefn *poFldDefn = poFeatureDefn->GetFieldDefn(panMap[iField]);

        sprintf( pszFieldListForSelect+strlen(pszFieldListForSelect),
                 ", \"%s\"", OGRSQLiteEscapeName(poFldDefn->GetNameRef()).c_str() );

        sprintf( pszNewFieldList+strlen(pszNewFieldList),
                ", '%s' %s", OGRSQLiteEscape(poFldDefn->GetNameRef()).c_str(),
                FieldDefnToSQliteFieldDefn(poFldDefn).c_str() );
    }


    CPLString osErrorMsg;
    osErrorMsg.Printf("Failed to reorder fields from table %s",
                  poFeatureDefn->GetName());

    eErr = RecreateTable(pszFieldListForSelect,
                                pszNewFieldList,
                                osErrorMsg.c_str());

    CPLFree( pszFieldListForSelect );
    CPLFree( pszNewFieldList );

    if (eErr != OGRERR_NONE)
        return eErr;


    return poFeatureDefn->ReorderFieldDefns( panMap );
}
