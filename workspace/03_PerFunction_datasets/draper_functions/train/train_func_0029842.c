audioCreatePlaybackBin(GnashAudioPrivate *audio)
{
    GstElement* autosink;
    GstPad* pad;
    gboolean ok;

    audio->_audioPlaybackBin = gst_bin_new("playbackBin");

    if ((autosink = gst_element_factory_make ("autoaudiosink", "audiosink")) == NULL) {
        log_error(_("%s: There was a problem making the audiosink!"), __FUNCTION__);
         return false;
    }

    ok = gst_bin_add(GST_BIN(audio->_audioPlaybackBin), autosink);


    pad = gst_element_get_pad (autosink, "sink");
    gst_element_add_pad (audio->_audioPlaybackBin, gst_ghost_pad_new ("sink", pad));
    gst_object_unref (GST_OBJECT (pad));

    return ok;
}
