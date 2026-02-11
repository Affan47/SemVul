_output_data (void)
{
  int exit_val;

  if (ipmidetect_load_data (handle, hostname, port, 0) < 0)
    {
      int errnum = ipmidetect_errnum (handle);
      char *msg = ipmidetect_errormsg (handle);


      if (errnum == IPMIDETECT_ERR_CONF_PARSE)
        err_exit ("Parse error in conf file");
      else if (errnum == IPMIDETECT_ERR_CONNECT)
        err_exit ("Cannot connect to server");
      else if (errnum == IPMIDETECT_ERR_CONNECT_TIMEOUT)
        err_exit ("Timeout connecting to server");
      else if (errnum == IPMIDETECT_ERR_HOSTNAME_INVALID)
        err_exit ("Invalid hostname");
      else
        err_exit ("%s: ipmidetect_load_data(): %s", __FUNCTION__, msg);
    }

  _get_nodes (detected_nodes,
              IPMIDETECT_BUFFERLEN,
              IPMIDETECT_DETECTED_NODES,
              &detected_count);

  _get_nodes (undetected_nodes,
              IPMIDETECT_BUFFERLEN,
              IPMIDETECT_UNDETECTED_NODES,
              &undetected_count);


  if (output_type == IPMIDETECT_DETECTED_AND_UNDETECTED_NODES)
    {
      if (output_format == '\n')
        {

          snprintf (detectedfmt,
                    IPMIDETECT_FORMATLEN,
                    "detected %d:",
                    detected_count);
          snprintf (undetectedfmt,
                    IPMIDETECT_FORMATLEN,
                    "undetected %d:",
                    undetected_count);
        }
      else
        _create_formats (": ");

      fprintf (stdout, detectedfmt, detected_count);

      _output_nodes (detected_nodes);


      if (output_format == '\n')
        fprintf (stdout, "\n");

      fprintf (stdout, undetectedfmt, undetected_count);

      _output_nodes (undetected_nodes);
    }
  else if (output_type == IPMIDETECT_DETECTED_NODES)
    _output_nodes (detected_nodes);
  else
    _output_nodes (undetected_nodes);

  if (output_type == IPMIDETECT_DETECTED_AND_UNDETECTED_NODES)
    exit_val = 0;
  else if (output_type == IPMIDETECT_DETECTED_NODES)
    exit_val = (!undetected_count) ? 0 : 1;
  else
    exit_val = (!detected_count) ? 0 : 1;

  return (exit_val);
}
