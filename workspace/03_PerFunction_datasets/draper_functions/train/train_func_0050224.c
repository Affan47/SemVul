SetIntSubfield( const char *pszField, int iFieldIndex,
                               const char *pszSubfield, int iSubfieldIndex,
                               int nNewValue )

{


    DDFField *poField;

    poField = FindField( pszField, iFieldIndex );
    if( poField == NULL )
        return FALSE;


    DDFSubfieldDefn     *poSFDefn;

    poSFDefn = poField->GetFieldDefn()->FindSubfieldDefn( pszSubfield );
    if( poSFDefn == NULL )
        return FALSE;


    int nFormattedLen;

    if( !poSFDefn->FormatIntValue( NULL, 0, &nFormattedLen, nNewValue ) )
        return FALSE;


    int         nMaxBytes;
    char *pachSubfieldData = (char *)
        poField->GetSubfieldData(poSFDefn, &nMaxBytes,
                                 iSubfieldIndex);


    if( nMaxBytes == 0
        || (nMaxBytes == 1 && pachSubfieldData[0] == DDF_FIELD_TERMINATOR) )
    {
        CreateDefaultFieldInstance( poField, iSubfieldIndex );


        pachSubfieldData = (char *)
            poField->GetSubfieldData(poSFDefn, &nMaxBytes,
                                     iSubfieldIndex);
    }


    int nExistingLength;

    poSFDefn->GetDataLength( pachSubfieldData, nMaxBytes, &nExistingLength );

    if( nExistingLength == nFormattedLen )
    {
        return poSFDefn->FormatIntValue( pachSubfieldData, nFormattedLen,
                                         NULL, nNewValue );
    }


    const char *pachFieldInstData;
    int         nInstanceSize, nStartOffset, nSuccess;
    char *pachNewData;

    pachFieldInstData = poField->GetInstanceData( iFieldIndex,
                                                  &nInstanceSize );

    nStartOffset = pachSubfieldData - pachFieldInstData;

    pachNewData = (char *) CPLMalloc(nFormattedLen);
    poSFDefn->FormatIntValue( pachNewData, nFormattedLen, NULL,
                              nNewValue );

    nSuccess = UpdateFieldRaw( poField, iFieldIndex,
                               nStartOffset, nExistingLength,
                               pachNewData, nFormattedLen );

    CPLFree( pachNewData );

    return nSuccess;
}
