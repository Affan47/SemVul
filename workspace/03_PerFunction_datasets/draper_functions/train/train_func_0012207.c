flickcurl_call_get_one_string_field(flickcurl* fc,
                                    const char* key, const char* value,
                                    const char* method,
                                    const xmlChar* xpathExpr)
{
  char *result = NULL;
  xmlDocPtr doc = NULL;
  xmlXPathContextPtr xpathCtx = NULL;

  flickcurl_init_params(fc, 0);
  if(key && value) {
    flickcurl_add_param(fc, key, value);
  }

  flickcurl_end_params(fc);

  if(flickcurl_prepare(fc, method))
    goto tidy;

  doc = flickcurl_invoke(fc);
  if(!doc)
    goto tidy;

  xpathCtx = xmlXPathNewContext(doc);
  if(xpathCtx)
    result = flickcurl_xpath_eval(fc, xpathCtx, xpathExpr);

  xmlXPathFreeContext(xpathCtx);

  tidy:

  return result;
}
