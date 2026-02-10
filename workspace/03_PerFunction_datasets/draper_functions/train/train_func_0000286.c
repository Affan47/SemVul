queueLoad()
{
    if ( ! _onLoadCalled ) {
        _onLoadCalled = true;

        if ( ! parent() && getSWFVersion(*getObject(this)) < 6 ) return;
        queueEvent(event_id(event_id::LOAD),
                    movie_root::PRIORITY_DOACTION);
    }
}
