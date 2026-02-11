flickcurl_build_video(flickcurl* fc, xmlXPathContextPtr xpathCtx,
                      const xmlChar* xpathExpr)
{
  flickcurl_video* v = NULL;
  int nodes_count;
  int i;
  xmlXPathObjectPtr xpathObj = NULL;
  xmlNodeSetPtr nodes;
  int count = 0;


  xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
  if(!xpathObj) {
    flickcurl_error(fc, "Unable to evaluate XPath expression \"%s\"",
                    xpathExpr);
    fc->failed = 1;
    goto tidy;
  }

  nodes = xpathObj->nodesetval;

  nodes_count = xmlXPathNodeSetGetLength(nodes);

  v = (flickcurl_video*)calloc(1, sizeof(flickcurl_video));
  if(!v) {
    flickcurl_error(fc, "Unable to allocate the memory needed for video.");
    fc->failed = 1;
    goto tidy;
  }


  for(i = 0; i < nodes_count; i++) {
    xmlNodePtr node = nodes->nodeTab[i];
    xmlAttr* attr;
    const char *node_name = (const char*)node->name;

    if(node->type != XML_ELEMENT_NODE) {
      flickcurl_error(fc, "Got unexpected node type %d", node->type);
      fc->failed = 1;
      break;
    }

    if(strcmp(node_name, "video"))
      continue;

    count++;

    for(attr = node->properties; attr; attr = attr->next) {
      const char *attr_name = (const char*)attr->name;
      int attr_value = atoi((const char*)attr->children->content);
      if(!strcmp(attr_name, "ready"))
        v->ready = attr_value;
      else if(!strcmp(attr_name, "failed"))
        v->failed = attr_value;
      else if(!strcmp(attr_name, "pending"))
        v->pending = attr_value;
      else if(!strcmp(attr_name, "duration"))
        v->duration = attr_value;
      else if(!strcmp(attr_name, "width"))
        v->width = attr_value;
      else if(!strcmp(attr_name, "height"))
        v->height = attr_value;
    }

  }

  if(!count) {
    flickcurl_free_video(v);
    v = NULL;
  }
#if FLICKCURL_DEBUG > 1
else {
    fprintf(stderr, "video: ready %d  failed %d  pending %d  duration %d  width %d  height %d\n",
            v->ready, v->failed, v->pending, v->duration,
            v->width, v->height);
  }
#endif

 tidy:
  if(xpathObj)
    xmlXPathFreeObject(xpathObj);

  return v;
}
