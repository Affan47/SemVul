makeAudioSourcePlaybackLink(GnashAudioPrivate *audio)
{
    if (gst_bin_get_by_name(GST_BIN(audio->_pipeline), "playbackBin") == NULL) {
        gst_object_ref(audio->_audioPlaybackBin);
        gst_bin_add(GST_BIN(audio->_pipeline), audio->_audioPlaybackBin);
    }

    GstPad *audioPlaybackQueueSrc, *audioPlaybackBinSink;
    GstPadLinkReturn padreturn;

    audioPlaybackQueueSrc = gst_element_get_pad(audio->_audioMainBin,
        "audioPlaybackQueueSrc");
    audioPlaybackBinSink = gst_element_get_pad(audio->_audioPlaybackBin,
        "sink");

    padreturn = gst_pad_link(audioPlaybackQueueSrc, audioPlaybackBinSink);

    if (padreturn == GST_PAD_LINK_OK) {
        return true;
    } else {
        log_error(_("something went wrong in the makeSourcePlaybackLink function"));
        return false;
    }
}
