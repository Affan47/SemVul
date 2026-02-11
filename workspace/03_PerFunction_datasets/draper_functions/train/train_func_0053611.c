writeCom( void )
{
    ExifStatus status = EXIF_OK ;
    unsigned int numOfCom = mComMarkerList.size() ;
    uint8 commark[] = { 0xFF, M_COM };
    tsize_t dataSize = 0;
    uint8 tagSize[2];
    for ( unsigned int i = 0; (i < numOfCom) && (status == EXIF_OK); i++ )
    {
        ExifComMarker * marker = mComMarkerList.getComMarker(i);
        uint8 * comdata = ( uint8 * )marker->getData(dataSize);
        if ((comdata != NULL) &&
            (mExifio->write((tdata_t)&commark[0],2*sizeof (uint8)) == 2*sizeof(uint8) ))
        {
            tsize_t tmpTagSize = dataSize+2;
            tagSize[1] = tmpTagSize & 0x000000FF;
            tagSize[0] = (tmpTagSize>>8) & 0x000000FF;
            if (mExifio->write((tdata_t)&tagSize[0],2*sizeof (uint8)) == 2*sizeof (uint8) )
            {
                if( mExifio->write((tdata_t)comdata,dataSize) != dataSize )
                {
                    status =  EXIF_FILE_WRITE_ERROR ;
                }
            }
            else
                status =  EXIF_FILE_WRITE_ERROR ;
        }
        else
            status =  EXIF_FILE_WRITE_ERROR ;
    }
    return status;
}
