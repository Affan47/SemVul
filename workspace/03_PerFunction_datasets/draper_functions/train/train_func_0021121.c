flickcurl_build_blog_services(flickcurl* fc, xmlXPathContextPtr xpathCtx,
                              const xmlChar* xpathExpr,
                              int* blog_services_count_p)
{
  flickcurl_blog_service** blog_services = NULL;
  int nodes_count;
  int blog_services_count;
  int i;
  xmlXPathObjectPtr xpathObj = NULL;
  xmlNodeSetPtr nodes;

  xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
  if(!xpathObj) {
    flickcurl_error(fc, "Unable to evaluate XPath expression \"%s\"",
                    xpathExpr);
    fc->failed = 1;
    goto tidy;
  }

  nodes = xpathObj->nodesetval;

  nodes_count = xmlXPathNodeSetGetLength(nodes);
  blog_services = (flickcurl_blog_service**)calloc(sizeof(flickcurl_blog_service*), nodes_count+1);

  for(i = 0, blog_services_count = 0; i < nodes_count; i++) {
    xmlNodePtr node = nodes->nodeTab[i];
    xmlAttr* attr;
    flickcurl_blog_service* b;
    xmlNodePtr chnode;

    if(node->type != XML_ELEMENT_NODE) {
      flickcurl_error(fc, "Got unexpected node type %d", node->type);
      fc->failed = 1;
      break;
    }

    b = (flickcurl_blog_service*)calloc(sizeof(flickcurl_blog_service), 1);

    for(attr = node->properties; attr; attr = attr->next) {
      size_t attr_len = strlen((const char*)attr->children->content);
      const char *attr_name = (const char*)attr->name;
      char *attr_value;

      attr_value = (char*)malloc(attr_len + 1);
      memcpy(attr_value, attr->children->content, attr_len + 1);

      if(!strcmp(attr_name, "id"))
        b->id = attr_value;
      else
        free(attr_value);
    }

    for(chnode = node->children; chnode; chnode = chnode->next) {
      if(chnode->type == XML_TEXT_NODE) {
        size_t len = strlen((const char*)chnode->content);
        b->name = (char*)malloc(len + 1);
        memcpy(b->name, chnode->content, len + 1);
      }
    }

#if FLICKCURL_DEBUG > 1
    fprintf(stderr, "blog service: id %s  name '%s'\n", b->id, b->name);
#endif

    blog_services[blog_services_count++] = b;
  }

  if(blog_services_count_p)
    *blog_services_count_p = blog_services_count;

 tidy:
  if(xpathObj)
    xmlXPathFreeObject(xpathObj);

  return blog_services;
}
