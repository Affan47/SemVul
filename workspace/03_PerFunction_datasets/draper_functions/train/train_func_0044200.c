setComposer( Composer *composer )
{
    if( m_composer )
        static_cast<Composer *>( m_composer.data() )->removeTrack( this );
    if( composer )
        composer->addTrack( this );
    m_composer = Meta::ComposerPtr( composer );
}
