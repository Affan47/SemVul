read(QImage *outImage)
{
    QDataStream s( device() );
    s.setByteOrder( QDataStream::BigEndian );


    RasHeader ras;
    s >> ras;

    s.device()->seek( RasHeader::SIZE + ras.Length + ras.ColorMapLength );


    if( !s.atEnd() && ras.Type != 2) {
        kDebug(399) << "This RAS file is not valid, or an older version of the format.";
        return false;
    }


    if( !IsSupported(ras) ) {
        kDebug(399) << "This RAS file is not supported.";
        return false;
    }

    QImage img;
    bool result = LoadRAS(s, ras, img);

    if( result == false ) {
        kDebug(399) << "Error loading RAS file.";
        return false;
    }

    *outImage = img;
    return true;
}
