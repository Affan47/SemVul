append( Track track, QString const tag )
{
    SetTagRequest *request = new SetTagRequest;
    request->setType( UnicornEnums::ItemTrack );
    request->setMode( TAG_APPEND );
    request->setTag( tag );
    request->setArtist( track.artist() );
    request->setToken( track.title() );
    request->start();

    return request;
}
