flickcurl_photos_geo_removeLocation(flickcurl* fc, const char* photo_id)
{
  xmlDocPtr doc = NULL;

  flickcurl_init_params(fc, 1);

  if(!photo_id)
    return 1;

  flickcurl_add_param(fc, "photo_id", photo_id);

  flickcurl_end_params(fc);

  if(flickcurl_prepare(fc, "flickr.photos.geo.removeLocation"))
    goto tidy;

  doc = flickcurl_invoke(fc);
  if(!doc)
    goto tidy;

  tidy:

  return fc->failed;
}
