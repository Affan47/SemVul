apply( DcmFileFormat& dcmfile ) const
{
    DcmDataset* const dataset = dcmfile.getDataset();
    return dataset && apply( *dataset );
}
