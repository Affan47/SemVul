CreateMetadata( HDF5GroupObjects *poH5Object, int nType)
{
    hid_t       hGroupID;
    hid_t       hDatasetID;
    int         nbAttrs;

    HDF5Dataset *poDS;

    if( !poH5Object->pszPath )
        return CE_None;

    poDS = this;

    poH5CurrentObject = poH5Object;
    nbAttrs = poH5Object->nbAttrs;

    if( poH5Object->pszPath == NULL || EQUAL(poH5Object->pszPath, "" ) )
        return CE_None;

    switch( nType ) {

    case H5G_GROUP:

        if( nbAttrs > 0 ) {
            hGroupID = H5Gopen( hHDF5, poH5Object->pszPath );
            H5Aiterate( hGroupID, NULL, HDF5AttrIterate, (void *)poDS  );
            H5Gclose( hGroupID );
        }

        break;

    case H5G_DATASET:

        if( nbAttrs > 0 ) {
            hDatasetID =  H5Dopen(hHDF5, poH5Object->pszPath );
            H5Aiterate( hDatasetID, NULL, HDF5AttrIterate, (void *)poDS );
            H5Dclose( hDatasetID );
        }
        break;

    default:
        break;
    }

    return CE_None;
}
