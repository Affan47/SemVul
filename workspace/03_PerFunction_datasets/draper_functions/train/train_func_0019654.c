frame( const QObject *obj )
{
    assert( obj->inherits( "KParts::ReadOnlyPart" ) );
    const KParts::ReadOnlyPart* const part = static_cast<const KParts::ReadOnlyPart *>( obj );

    FrameIt it = d->m_frames.begin();
    const FrameIt end = d->m_frames.end();
    for (; it != end; ++it ) {
        if ((*it)->m_part.data() == part )
            return *it;
    }

    FrameIt oi = d->m_objects.begin();
    const FrameIt oiEnd = d->m_objects.end();
    for (; oi != oiEnd; ++oi ) {
        if ((*oi)->m_part.data() == part)
            return *oi;
    }

    return 0L;
}
