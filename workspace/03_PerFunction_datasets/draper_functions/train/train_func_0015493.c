read(QImage *image)
{
    QDataStream s( device() );
    s.setByteOrder( QDataStream::LittleEndian );


    uint fourcc;
    s >> fourcc;
    if( fourcc != FOURCC_DDS ) {
        kDebug(399) << "This is not a DDS file.";
        return false;
    }


    DDSHeader header;
    s >> header;


    if( s.atEnd() || !IsValid( header ) ) {
        kDebug(399) << "This DDS file is not valid.";
        return false;
    }


    if( !IsSupported( header ) ) {
        kDebug(399) << "This DDS file is not supported.";
        return false;
    }

    bool result;

    if( IsCubeMap( header ) ) {
        result = LoadCubeMap( s, header, *image );
    }
    else {
        result = LoadTexture( s, header, *image );
    }

    return result;
}
