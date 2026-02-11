flickcurl_places_placesForBoundingBox(flickcurl* fc,
                                      flickcurl_place_type place_type,
                                      double minimum_longitude,
                                      double minimum_latitude,
                                      double maximum_longitude,
                                      double maximum_latitude)
{
  xmlDocPtr doc = NULL;
  xmlXPathContextPtr xpathCtx = NULL;
  flickcurl_place** places = NULL;
  char place_type_id_str[3];
  int place_type_id = -1;
  char bbox[255];

  flickcurl_init_params(fc, 0);

  place_type_id = flickcurl_place_type_to_id(place_type);
  if(place_type_id < 0)
    return NULL;

  sprintf(bbox, "%f,%f,%f,%f",  minimum_longitude, minimum_latitude,
          maximum_longitude, maximum_latitude);
  flickcurl_add_param(fc, "bbox", bbox);


  sprintf(place_type_id_str, "%d", place_type_id);
  flickcurl_add_param(fc, "place_type_id", place_type_id_str);

  flickcurl_end_params(fc);

  if(flickcurl_prepare(fc, "flickr.places.placesForBoundingBox"))
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

  places = flickcurl_build_places(fc, xpathCtx,
                                  (const xmlChar*)"/rsp/places/place", NULL);

  tidy:
  if(xpathCtx)
    xmlXPathFreeContext(xpathCtx);

  if(fc->failed)
    places = NULL;

  return places;
}
