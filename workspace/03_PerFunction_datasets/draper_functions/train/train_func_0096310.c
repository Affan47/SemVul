parse_asx(bgav_redirector_context_t * r)
  {
  int result;
  bgav_yml_node_t * node;


  node = bgav_yml_parse(r->input);

  if(!node)
    {

    bgav_log(r->opt, BGAV_LOG_ERROR, LOG_DOMAIN, "Parse asx failed (yml error)");
    return 0;
    }
  result = xml_2_asx(r, node);

  bgav_yml_free(node);

  if(!result)
    bgav_log(r->opt, BGAV_LOG_ERROR, LOG_DOMAIN, "Parse asx failed");

  return result;
  }
