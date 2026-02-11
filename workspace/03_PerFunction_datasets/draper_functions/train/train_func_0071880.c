gst_curl_smtp_sink_prepare_transfer (GstCurlBaseSink * bcsink)
{
  GstCurlSmtpSink *sink = GST_CURL_SMTP_SINK (bcsink);
  CURLcode res;
  gboolean ret = TRUE;

  if (sink->pop_location && strlen (sink->pop_location)) {
    if ((sink->pop_curl = curl_easy_init ()) == NULL) {
      GST_DEBUG_OBJECT (sink, "POP protocol: failed to create handler");
      GST_ELEMENT_ERROR (sink, RESOURCE, WRITE,
          ("POP protocol: failed to create handler"), (NULL));

      return FALSE;
    }

    curl_easy_setopt (sink->pop_curl, CURLOPT_URL, sink->pop_location);
    if (sink->pop_user != NULL && strlen (sink->pop_user) &&
        sink->pop_passwd != NULL && strlen (sink->pop_passwd)) {
      curl_easy_setopt (sink->pop_curl, CURLOPT_USERNAME, sink->pop_user);
      curl_easy_setopt (sink->pop_curl, CURLOPT_PASSWORD, sink->pop_passwd);
    }
  }

  if (sink->pop_curl == NULL) {
    goto end;
  }


  res = curl_easy_perform (sink->pop_curl);
  if (res != CURLE_OK) {
    GST_DEBUG_OBJECT (sink, "POP transfer failed: %s",
        curl_easy_strerror (res));
    GST_ELEMENT_ERROR (sink, RESOURCE, WRITE, ("POP transfer failed: %s",
            curl_easy_strerror (res)), (NULL));

    ret = FALSE;
  }

  curl_easy_cleanup (sink->pop_curl);
  sink->pop_curl = NULL;

end:
  return ret;
}
