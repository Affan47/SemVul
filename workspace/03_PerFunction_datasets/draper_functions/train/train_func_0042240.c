flickcurl_build_tickets(flickcurl* fc, xmlXPathContextPtr xpathCtx,
                      const xmlChar* xpathExpr, int* ticket_count_p)
{
  flickcurl_ticket** tickets = NULL;
  int nodes_count;
  int ticket_count;
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
  tickets = (flickcurl_ticket**)calloc(sizeof(flickcurl_ticket*), nodes_count+1);

  for(i = 0, ticket_count = 0; i < nodes_count; i++) {
    xmlNodePtr node = nodes->nodeTab[i];
    xmlAttr* attr;
    flickcurl_ticket* t;

    if(node->type != XML_ELEMENT_NODE) {
      flickcurl_error(fc, "Got unexpected node type %d", node->type);
      fc->failed = 1;
      break;
    }

    t = (flickcurl_ticket*)calloc(sizeof(flickcurl_ticket), 1);

    for(attr = node->properties; attr; attr = attr->next) {
      size_t attr_len = strlen((const char*)attr->children->content);
      const char *attr_name = (const char*)attr->name;
      char *attr_value;

      attr_value = (char*)malloc(attr_len + 1);
      memcpy(attr_value, attr->children->content, attr_len + 1);

      if(!strcmp(attr_name, "id")) {
        t->id = atoi(attr_value);
        free(attr_value);
      } else if(!strcmp(attr_name, "complete")) {
        t->complete = atoi(attr_value);
        free(attr_value);
      } else if(!strcmp(attr_name, "photoid")) {
        t->photoid = atoi(attr_value);
        free(attr_value);
      } else if(!strcmp(attr_name, "invalid")) {
        t->invalid = atoi(attr_value);
        free(attr_value);
      } else
        free(attr_value);
    }

#if FLICKCURL_DEBUG > 1
    fprintf(stderr, "ticket: label %s width %d height %d  source %s url %s\n",
            t->label, t->width, t->height, t->source, t->url);
#endif

    tickets[ticket_count++] = t;
  }

  if(ticket_count_p)
    *ticket_count_p = ticket_count;

 tidy:
  if(xpathObj)
    xmlXPathFreeObject(xpathObj);

  return tickets;
}
