volumeChanged( int newVolume )
{
    if ( newVolume < 34 )
        setIcon( KIcon( "audio-volume-low" ) );
    else if ( newVolume < 67 )
        setIcon( KIcon( "audio-volume-medium" ) );
    else
        setIcon( KIcon( "audio-volume-high" ) );

    m_volumeLabel->setText( QString::number( newVolume ) + '%' );

    if( newVolume != m_volumeSlider->value() )
        m_volumeSlider->setValue( newVolume );


    if ( newVolume )
        m_muteAction->setChecked( false );

    setToolTip( i18n( "Volume: %1% %2", newVolume, ( m_muteAction->isChecked() ? i18n( "(muted)" ) : "" ) ) );
}
