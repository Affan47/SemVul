reliableTrackMetaData() const
{
    if( id().startsWith("amarok-nepomuk:") )
        return Meta::valTitle | Meta::valArtist | Meta::valAlbum | Meta::valComposer |
               Meta::valTrackNr;
    else
        return Meta::valTitle | Meta::valArtist | Meta::valAlbum |
               Meta::valComposer | Meta::valYear | Meta::valTrackNr | Meta::valDiscNr;
}
