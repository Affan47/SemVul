audioChangeSourceBin(GnashAudioPrivate *audio)
{
    GError *error = NULL;
    gchar *command = NULL;

    if (audio->_pipelineIsPlaying == true) {
        audioStop(audio);
    }


    if (!(GST_ELEMENT_PARENT(audio->_audioSourceBin) == NULL)) {
        gst_bin_remove(GST_BIN(audio->_audioMainBin),
                audio->_audioSourceBin);
        audio->_audioSourceBin = NULL;
    }

    if (strcmp(audio->_deviceName, "audiotest") == 0) {
        log_debug("%s: You don't have any mics chosen, using audiotestsrc",
            __FUNCTION__);
        audio->_audioSourceBin = gst_parse_bin_from_description (
            "audiotestsrc name=audioSource",
            TRUE, &error);
        log_debug("Command: audiotestsrc name=audioSource");
        audio->audioSource = gst_bin_get_by_name (
                GST_BIN (audio->_audioSourceBin), "audioSource");
        return true;
    }

    command = g_strdup_printf ("%s name=audioSource device=%s ! capsfilter name=capsfilter caps=audio/x-raw-int,signed=true,channels=2,rate=%i;audio/x-raw-float,channels=2,rate=%i ! rgvolume pre-amp=%f",
        audio->_audioDevice->getGstreamerSrc(),
        audio->_audioDevice->getDevLocation(),
        _rate, _rate, gstgain());

    log_debug ("GstPipeline command is: %s\n", command);

    audio->_audioSourceBin = gst_parse_bin_from_description(command, TRUE,
                                &error);
    if (audio->_audioSourceBin == NULL) {
        log_error(_("%s: Creation of the audioSourceBin failed"),
            __FUNCTION__);
        log_error(_("the error was %s"), error->message);
        return false;
    }
    g_free(command);
    audio->audioSource = gst_bin_get_by_name(
            GST_BIN (audio->_audioSourceBin), "audioSource");

    gboolean result;
    result = gst_bin_add(GST_BIN(audio->_audioMainBin),
            audio->_audioSourceBin);
    if (!result) {
        log_error(_("%s: couldn't drop the sourcebin back into the main bin"),
            __FUNCTION__);
        return false;
    }

    GstElement *tee = gst_bin_get_by_name(GST_BIN(audio->_audioMainBin),
        "tee");
    result = gst_element_link(audio->_audioSourceBin, tee);

    if (!result) {
        log_error(_("%s: couldn't link up sourcebin and tee"), __FUNCTION__);
        return false;
    }
    _globalAudio = audio;
    return true;
}
