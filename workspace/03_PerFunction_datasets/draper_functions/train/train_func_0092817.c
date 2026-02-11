get_audiosink_element()
{

    static int numGnashRcSinks = 0;


    const std::string GNASHRCSINK = "gnashrcsink";
    const std::string sAudioSink =
      RcInitFile::getDefaultInstance().getGstAudioSink();


    GstElement* element;

    if(sAudioSink.find('!') != std::string::npos)
    {
        element = gst_parse_bin_from_description(sAudioSink.c_str(), true, NULL);
        if(element != NULL)
        {
           std::ostringstream o;
           o << numGnashRcSinks++;
           gst_element_set_name(element, (GNASHRCSINK + o.str()).c_str());
        }
    }
    else
    {
        element = gst_element_factory_make(sAudioSink.c_str(), NULL);
    }

    if(!element)
    {
        log_debug(_("Unable to retrieve a valid audio sink from ~/.gnashrc"));

        element = gst_element_factory_make("autoaudiosink", NULL);

        if(!element)
        {
            log_debug(_("Unable to retrieve a valid audio sink from autoaudiosink"));

            element = gst_element_factory_make("gconfaudiosink", NULL);

            if(!element)
                log_error(_("Unable to retrieve a valid audio sink from gconfaudiosink\n%s"),
                        _("Sink search exhausted: you won't be able to hear sound!"));
        }
    }

    if(element)
    {
        log_debug(_("Got a non-NULL audio sink; its wrapper name is: %s"), _(GST_ELEMENT_NAME(element)));
    }

    return element;
}
