flickcurl_galleries_addPhoto(flickcurl* fc, const char* gallery_id,
                             const char* photo_id, const char* comment_text)
{
  xmlDocPtr doc = NULL;
  xmlXPathContextPtr xpathCtx = NULL;
  void* result = NULL;

  flickcurl_init_params(fc, 1);

  if(!gallery_id || !photo_id)
    return 1;

  flickcurl_add_param(fc, "gallery_id", gallery_id);
  flickcurl_add_param(fc, "photo_id", photo_id);
  if(comment_text) {
    flickcurl_add_param(fc, "comment", comment_text);
  }

  flickcurl_end_params(fc);

  if(flickcurl_prepare(fc, "flickr.galleries.addPhoto"))
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

  result = NULL;

  tidy:
  if(xpathCtx)
    xmlXPathFreeContext(xpathCtx);

  if(fc->failed)
    result = NULL;

  return (result == NULL);
}
