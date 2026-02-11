detachAuxStreamer()
{
    if ( ! _soundHandler ) return;
    if ( !_auxStreamer )
    {
        log_debug("detachAuxStreamer called while not attached");
        return;
    }
    _soundHandler->unplugInputStream(_auxStreamer);
    _auxStreamer = 0;
}
