flickcurl_photos_getCounts(flickcurl* fc,
                           const char** dates_array,
                           const char** taken_dates_array)
{
  xmlDocPtr doc = NULL;
  xmlXPathContextPtr xpathCtx = NULL;
  int** counts = NULL;
  char* dates = NULL;
  char* taken_dates = NULL;

  flickcurl_init_params(fc, 0);


  if(!dates_array && !taken_dates_array)
    return NULL;

  if(dates_array) {
    dates = flickcurl_array_join(dates_array, ',');
    flickcurl_add_param(fc, "dates", dates);
  }
  if(taken_dates_array) {
    taken_dates = flickcurl_array_join(taken_dates_array, ',');
    flickcurl_add_param(fc, "taken_dates", taken_dates);
  }

  flickcurl_end_params(fc);

  if(flickcurl_prepare(fc, "flickr.photos.getCounts"))
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

  counts = flickcurl_build_photocounts(fc, xpathCtx,
                                     (const xmlChar*)"/rsp/photocounts/photocount",
                                     NULL);

  tidy:
  if(xpathCtx)
    xmlXPathFreeContext(xpathCtx);

  if(fc->failed) {
    if(counts)
      free(counts);
    counts = NULL;
  }

  if(dates)
    free(dates);

  if(taken_dates)
    free(taken_dates);

  return counts;
}
