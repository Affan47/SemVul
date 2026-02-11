defaultEventHandler(EventImpl *evt)
{
    if ( evt->id() == EventImpl::KHTML_CONTENTLOADED_EVENT && !evt->propagationStopped() && !evt->defaultPrevented() )
        contentLoaded();
}
