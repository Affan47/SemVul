plugInputStream(std::auto_ptr<InputStream> newStreamer)
{
#ifdef GNASH_DEBUG_SOUNDS_MANAGEMENT
    InputStream* newStream = newStreamer.get();
#endif

    if (!_inputStreams.insert(newStreamer.release()).second) {

        log_error(_("_inputStreams container still has a pointer "
                    "to deleted InputStream %p!"), newStreamer.get());

        abort();
    }

#ifdef GNASH_DEBUG_SOUNDS_MANAGEMENT
    log_debug("Plugged InputStream %p", newStream);
#endif


    ++_soundsStarted;
}
