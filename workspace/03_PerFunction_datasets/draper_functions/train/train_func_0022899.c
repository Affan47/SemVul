HDF5FindDatasetObjectsbyPath
    ( HDF5GroupObjects *poH5Objects, const char* pszDatasetPath )
{
    unsigned i;
    HDF5Dataset *poDS;
    HDF5GroupObjects *poObjectsFound;
    poDS=this;

    if( poH5Objects->nType == H5G_DATASET &&
        EQUAL( poH5Objects->pszUnderscorePath,pszDatasetPath ) ) {


        return( poH5Objects );
    }

    if( poH5Objects->nbObjs >0 )
        for( i=0; i <poH5Objects->nbObjs; i++ )   {
            poObjectsFound=
            poDS->HDF5FindDatasetObjectsbyPath( poH5Objects->poHchild+i,
                                                pszDatasetPath );


            if( poObjectsFound != NULL ) return( poObjectsFound );
        }


    return( NULL );

}
