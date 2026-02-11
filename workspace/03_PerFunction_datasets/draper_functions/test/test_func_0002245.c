updateToolTipIcon()
{
    updateToolTip();

    if( m_track )
    {
        if( m_track->album() && m_track->album()->hasImage() )
        {
            QPixmap image = The::svgHandler()->imageWithBorder( m_track->album(), KIconLoader::SizeLarge, 5 );
            setToolTipIconByPixmap( image );
        }
        else
        {
            setToolTipIconByName( "amarok" );
        }
    }
    else
    {
        setToolTipIconByName( "amarok" );
    }
}
