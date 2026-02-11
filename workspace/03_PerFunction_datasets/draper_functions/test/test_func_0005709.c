gst_udp_parse_uri (const gchar * uristr, GstUDPUri * uri)
{
  gchar *protocol, *location_start;
  gchar *location, *location_end;
  gchar *colptr;


  protocol = gst_uri_get_protocol (uristr);
  if (!protocol)
    goto no_protocol;
  if (strcmp (protocol, "udp") != 0)
    goto wrong_protocol;
  g_free (protocol);

  location_start = gst_uri_get_location (uristr);
  if (!location_start)
    return FALSE;

  GST_DEBUG ("got location '%s'", location_start);


  location = g_strstr_len (location_start, -1, "@");
  if (location == NULL)
    location = location_start;
  else
    location += 1;

  if (location[0] == '[') {
    GST_DEBUG ("parse IPV6 address '%s'", location);
    location_end = strchr (location, ']');
    if (location_end == NULL)
      goto wrong_address;

    uri->is_ipv6 = TRUE;
    g_free (uri->host);
    uri->host = g_strndup (location + 1, location_end - location - 1);
    colptr = strrchr (location_end, ':');
  } else {
    GST_DEBUG ("parse IPV4 address '%s'", location);
    uri->is_ipv6 = FALSE;
    colptr = strrchr (location, ':');

    g_free (uri->host);
    if (colptr != NULL) {
      uri->host = g_strndup (location, colptr - location);
    } else {
      uri->host = g_strdup (location);
    }
  }
  GST_DEBUG ("host set to '%s'", uri->host);

  if (colptr != NULL) {
    uri->port = atoi (colptr + 1);
  }
  g_free (location_start);

  return 0;


no_protocol:
  {
    GST_ERROR ("error parsing uri %s: no protocol", uristr);
    return -1;
  }
wrong_protocol:
  {
    GST_ERROR ("error parsing uri %s: wrong protocol (%s != udp)", uristr,
        protocol);
    g_free (protocol);
    return -1;
  }
wrong_address:
  {
    GST_ERROR ("error parsing uri %s", uristr);
    g_free (location);
    return -1;
  }
}
