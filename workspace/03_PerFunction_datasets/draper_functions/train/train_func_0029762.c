ProvideDataDDS()

{
    if( bDataLoaded )
        return poTargetVar != NULL;

    int bResult = OGRDODSLayer::ProvideDataDDS();

    if( !bResult )
        return bResult;

    int iArray;
    for( iArray=0; iArray < nArrayRefCount; iArray++ )
    {
        OGRDODSArrayRef *poRef = paoArrayRefs + iArray;
        BaseType *poTarget = poDataDDS->var( poRef->pszName );


        if( poTarget->type() == dods_grid_c )
        {
            Grid *poGrid = dynamic_cast<Grid *>( poTarget );
            poRef->poArray = dynamic_cast<Array *>(poGrid->array_var());

            if( iArray == 0 )
                poTargetGrid = poGrid;
        }
        else if( poTarget->type() == dods_array_c )
        {
            poRef->poArray = dynamic_cast<Array *>( poTarget );
        }
        else
        {
            CPLAssert( FALSE );
            return FALSE;
        }

        if( iArray == 0 )
            poTargetArray = poRef->poArray;


        poRef->pRawData = CPLMalloc( poRef->poArray->width() );
        poRef->poArray->buf2val( &(poRef->pRawData) );
    }


    if( poTargetGrid != NULL )
    {
        int iMap;
        Grid::Map_iter iterMap;

        for( iterMap = poTargetGrid->map_begin(), iMap = 0;
             iterMap != poTargetGrid->map_end();
             iterMap++, iMap++ )
        {
            paoDimensions[iMap].poMap = dynamic_cast<Array *>(*iterMap);
            paoDimensions[iMap].pRawData =
                CPLMalloc( paoDimensions[iMap].poMap->width() );
            paoDimensions[iMap].poMap->buf2val( &(paoDimensions[iMap].pRawData) );
        }
    }

    return bResult;
}
