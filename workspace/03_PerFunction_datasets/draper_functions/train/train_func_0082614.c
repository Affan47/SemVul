WriteNewBlockRecords( VSILFILE * fp )

{
    std::set<CPLString> aosAlreadyHandled;


    for( size_t iBlock=0; iBlock < poBlocksLayer->apoBlocks.size(); iBlock++ )
    {
        OGRFeature* poThisBlockFeat = poBlocksLayer->apoBlocks[iBlock];


        CPLString osBlockName = poThisBlockFeat->GetFieldAsString("BlockName");

        if( oHeaderDS.LookupBlock( osBlockName ) != NULL )
            continue;


        if( aosAlreadyHandled.find(osBlockName) != aosAlreadyHandled.end() )
            continue;

        aosAlreadyHandled.insert( osBlockName );


        WriteValue( fp, 0, "BLOCK_RECORD" );
        WriteEntityID( fp );
        WriteValue( fp, 100, "AcDbSymbolTableRecord" );
        WriteValue( fp, 100, "AcDbBlockTableRecord" );
        WriteValue( fp, 2, poThisBlockFeat->GetFieldAsString("BlockName") );
        if( !WriteValue( fp, 340, "0" ) )
            return FALSE;
    }

    return TRUE;
}
