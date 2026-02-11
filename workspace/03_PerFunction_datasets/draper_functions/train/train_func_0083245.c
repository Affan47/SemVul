command_photosets_getPhotos(flickcurl* fc, int argc, char *argv[])
{
  const char* photoset_id = argv[1];
  int privacy_filter= -1;
  flickcurl_photos_list* photos_list = NULL;
  flickcurl_photos_list_params list_params;
  int rc;

  flickcurl_photos_list_params_init(&list_params);

  if(argc > 2) {
    list_params.extras = argv[2];
    if(argc > 3) {
      privacy_filter = atoi(argv[3]);
      if(argc >4) {
        list_params.per_page = parse_page_param(argv[4]);
        if(argc >5) {
          list_params.page = parse_page_param(argv[5]);
          if(argc >6) {
            list_params.format = argv[6];
          }
        }
      }
    }
  }

  photos_list = flickcurl_photosets_getPhotos_params(fc, photoset_id,
                                                   privacy_filter,
                                                   &list_params);
  if(!photos_list)
    return 1;

  if(verbose)
    fprintf(stdout, "%s: Photoset %s photos (per_page %d  page %d):\n",
            program, photoset_id, list_params.per_page, list_params.page);

  rc = command_print_photos_list(fc, photos_list, output_fh, "Photo");
  flickcurl_free_photos_list(photos_list);

  return rc;
}
