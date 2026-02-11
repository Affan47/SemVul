flickcurl_people_getPhotos_params(flickcurl* fc, const char* user_id,
                                  int safe_search,
                                  const char* min_upload_date,
                                  const char* max_upload_date,
                                  const char* min_taken_date,
                                  const char* max_taken_date,
                                  int content_type,
                                  int privacy_filter,
                                  flickcurl_photos_list_params* list_params)
{
  flickcurl_photos_list* photos_list = NULL;
  const char* format = NULL;
  char safe_search_s[4];
  char content_type_s[4];
  char privacy_filter_s[4];

  flickcurl_init_params(fc, 0);

  if(!user_id)
    return NULL;

  flickcurl_add_param(fc, "user_id", user_id);
  if(safe_search >= 0 && safe_search < 10) {
    sprintf(safe_search_s, "%d", safe_search);
    flickcurl_add_param(fc, "safe_search", safe_search_s);
  }
  if(min_upload_date) {
    flickcurl_add_param(fc, "min_upload_date", min_upload_date);
  }
  if(max_upload_date) {
    flickcurl_add_param(fc, "max_upload_date", max_upload_date);
  }
  if(min_taken_date) {
    flickcurl_add_param(fc, "min_taken_date", min_taken_date);
  }
  if(max_taken_date) {
    flickcurl_add_param(fc, "max_taken_date", max_taken_date);
  }
  if(content_type >= 0 && content_type < 10) {
    sprintf(content_type_s, "%d", content_type);
    flickcurl_add_param(fc, "content_type", content_type_s);
  }
  if(privacy_filter >= 0 && privacy_filter < 10) {
    sprintf(privacy_filter_s, "%d", privacy_filter);
    flickcurl_add_param(fc, "privacy_filter", privacy_filter_s);
  }


  flickcurl_append_photos_list_params(fc, list_params, &format);

  flickcurl_end_params(fc);

  if(flickcurl_prepare(fc, "flickr.people.getPhotos"))
    goto tidy;

  photos_list = flickcurl_invoke_photos_list(fc,
                                             (const xmlChar*)"/rsp/photos",
                                             format);

  tidy:
  if(fc->failed) {
    if(photos_list)
      flickcurl_free_photos_list(photos_list);
    photos_list = NULL;
  }

  return photos_list;
}
