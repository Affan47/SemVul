Playing(const char *file)
{
        GstElement *pipeline, *filesrc;
        struct timeval time;

        gettimeofday(&time, NULL);
        if (!FLAG_ISSET(progdt.sndfgs, 0) || (difftimeval(time, timestamp) < 0.1))
                return;

        if (persist)
                EosMessageOccur(this);
        persist = true;
        filesrc = GST_ELEMENT(g_datalist_get_data(&eltset, "filesrc-element"));
        g_object_set(filesrc, "location", file, NULL);
        pipeline = GST_ELEMENT(g_datalist_get_data(&eltset, "pipeline-element"));
        gst_element_set_state(pipeline, GST_STATE_PLAYING);
        timestamp = time;
}
