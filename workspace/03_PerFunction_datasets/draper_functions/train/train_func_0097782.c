webcamMakeVideoDisplayLink()
{

    GnashWebcamPrivate* webcam = _globalWebcam;

    if (gst_bin_get_by_name(GST_BIN(webcam->_pipeline), "video_display_bin") == NULL) {
        gst_object_ref(webcam->_videoDisplayBin);
        gst_bin_add (GST_BIN(webcam->_pipeline), webcam->_videoDisplayBin);
    }

    GstPad *video_display_queue_src, *video_display_bin_sink;

    video_display_queue_src = gst_element_get_pad(webcam->_webcamMainBin,
        "video_display_queue_src");
    video_display_bin_sink = gst_element_get_pad(webcam->_videoDisplayBin,
        "sink");

    GstPadLinkReturn padreturn;
    padreturn = gst_pad_link(video_display_queue_src, video_display_bin_sink);

    if (padreturn == GST_PAD_LINK_OK) {
        return true;
    } else {
        log_error(_("something went wrong in the make_video_display_link function"));
        return false;
    }
}
