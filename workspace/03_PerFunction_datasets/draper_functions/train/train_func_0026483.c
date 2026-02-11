gst_cmml_parser_parse_start_element_ns (xmlParserCtxt * ctxt,
    const xmlChar * name, const xmlChar * prefix, const xmlChar * URI,
    int nb_preferences, const xmlChar ** namespaces,
    int nb_attributes, int nb_defaulted, const xmlChar ** attributes)
{
  GstCmmlParser *parser = (GstCmmlParser *) ctxt->_private;

  xmlSAX2StartElementNs (ctxt, name, prefix, URI, nb_preferences, namespaces,
      nb_attributes, nb_defaulted, attributes);

  if (parser->mode == GST_CMML_PARSER_ENCODE)
    if (!xmlStrcmp (name, (xmlChar *) "cmml"))
      if (parser->preamble_callback)

        gst_cmml_parser_parse_preamble (parser, NULL);
}
