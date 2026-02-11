redrawBookmarks( const QString *BookmarkName )
{
    DEBUG_BLOCK
    m_slider->clearTriangles();
    if ( The::engineController()->currentTrack() )
    {
        Meta::TrackPtr track = The::engineController()->currentTrack();
        if ( track->has<Capabilities::TimecodeLoadCapability>() )
        {
            Capabilities::TimecodeLoadCapability *tcl = track->create<Capabilities::TimecodeLoadCapability>();
            BookmarkList list = tcl->loadTimecodes();
            debug() << "found " << list.count() << " timecodes on this track";
            foreach( AmarokUrlPtr url, list )
            {
                if ( url->command() == "play" )
                {

                    if ( url->args().keys().contains( "pos" ) )
                    {
                        int pos = url->args().value( "pos" ).toDouble() * 1000;
                        debug() << "showing timecode: " << url->name() << " at " << pos ;
                        addBookmark( url->name(), pos, ( BookmarkName && BookmarkName == url->name() ));
                    }
                }
            }
            delete tcl;
        }
    }
}
