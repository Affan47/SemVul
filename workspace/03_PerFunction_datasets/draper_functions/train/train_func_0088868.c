flickcurl_photos_getAllContexts(flickcurl* fc, const char* photo_id)
{
  xmlDocPtr doc = NULL;
  flickcurl_context** contexts = NULL;

  flickcurl_init_params(fc, 0);

  flickcurl_add_param(fc, "photo_id", photo_id);

  flickcurl_end_params(fc);

  if(flickcurl_prepare(fc, "flickr.photos.getAllContexts"))
    goto tidy;

  doc = flickcurl_invoke(fc);
  if(!doc)
    goto tidy;

  contexts = flickcurl_build_contexts(fc, doc);

 tidy:
  if(fc->failed)
    contexts = NULL;

  return contexts;
}
