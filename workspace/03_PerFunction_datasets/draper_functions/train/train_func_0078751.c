incrementLoadedFrames()
{
    boost::mutex::scoped_lock lock(_frames_loaded_mutex);

    ++_frames_loaded;

    if ( _frames_loaded > m_frame_count )
    {
        IF_VERBOSE_MALFORMED_SWF(
            log_swferror(_("number of SHOWFRAME tags "
                "in SWF stream '%s' (%d) exceeds "
                "the advertised number in header (%d)."),
                get_url(), _frames_loaded,
                m_frame_count);
        )
    }

#ifdef DEBUG_FRAMES_LOAD
    log_debug("Loaded frame %u/%u", _frames_loaded, m_frame_count);
#endif


    if (_waiting_for_frame && _frames_loaded >= _waiting_for_frame )
    {


        _frame_reached_condition.notify_all();
    }

}
