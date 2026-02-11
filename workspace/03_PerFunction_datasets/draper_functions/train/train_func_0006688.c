flickcurl_prefs_getContentType(flickcurl* fc)
{
  xmlDocPtr doc = NULL;
  xmlXPathContextPtr xpathCtx = NULL;
  char* content_type_str = NULL;
  int content_type= -1;

  flickcurl_init_params(fc, 0);

  flickcurl_end_params(fc);

  if(flickcurl_prepare(fc, "flickr.prefs.getContentType"))
    goto tidy;

  doc = flickcurl_invoke(fc);
  if(!doc)
    goto tidy;


  xpathCtx = xmlXPathNewContext(doc);
  if(!xpathCtx) {
    flickcurl_error(fc, "Failed to create XPath context for document");
    fc->failed = 1;
    goto tidy;
  }

  content_type_str = flickcurl_xpath_eval(fc, xpathCtx,
                                          (const xmlChar*)"/rsp/person/@content_type");
  if(content_type_str) {
    content_type = atoi(content_type_str);
    free(content_type_str);
  }

  tidy:
  if(xpathCtx)
    xmlXPathFreeContext(xpathCtx);

  if(fc->failed)
    content_type= -1;

  return content_type;
}
