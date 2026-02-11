coverArtistLoaded( const QByteArray& to )
{

    ui.artistPic->setAlignment( Qt::AlignHCenter | Qt::AlignTop );

    if ( !render( to, ui.artistPic ) )
        setDefaultArtistPic();

    ui.artistPic->show();
}
