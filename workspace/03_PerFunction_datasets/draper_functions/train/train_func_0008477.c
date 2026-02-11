handleFLAC( TagLib::FLAC::File *file )
{
    if( file->readOnly() )
    {
        m_textStream << tr( "ERROR: File is read-only or could not be opened" ) << endl;
        return false;
    }

    TagLib::Ogg::XiphComment *comment = file->xiphComment( true );
    if( !comment )
        return false;

    if( handleXiphComment( comment, file ) )
    {
        file->save();
        return true;
    }

    return false;
}
