command_places_placesForContacts(flickcurl* fc, int argc, char *argv[])
{
  int usage = 0;
  flickcurl_place** places = NULL;
  flickcurl_place_type place_type = FLICKCURL_PLACE_LOCATION;
  int woe_id = -1;
  char* place_id = NULL;
  int threshold = -1;
  char* contacts = NULL;
  int min_upload_date = -1;
  int max_upload_date = -1;
  int min_taken_date = -1;
  int max_taken_date = -1;

  place_type = flickcurl_get_place_type_by_label(argv[1]);
  if(strcmp(argv[2], "-"))
     woe_id = atoi(argv[2]);
  if(strcmp(argv[3], "-"))
     place_id = argv[3];
  threshold = atoi(argv[4]);
  argv+= 5; argc-= 5;

  while(!usage && argc) {
    char* field = argv[0];
    argv++; argc--;

    if(!strcmp(field, "contacts")) {
      contacts = argv[0];
      argv++; argc--;
    } else if(!strcmp(field, "min-upload")) {
      min_upload_date = atoi(argv[0]);
      argv++; argc--;
    } else if(!strcmp(field, "max-upload")) {
      max_upload_date = atoi(argv[0]);
      argv++; argc--;
    } else if(!strcmp(field, "min-taken")) {
      min_taken_date = atoi(argv[0]);
      argv++; argc--;
    } else if(!strcmp(field, "max-taken")) {
      max_taken_date = atoi(argv[0]);
      argv++; argc--;
    } else {
      fprintf(stderr, "%s: Unknown parameter: '%s'\n", program, argv[0]);
      usage = 1;
    }
  }

  if(usage) {
    places = NULL;
    goto tidy;
  }

  places = flickcurl_places_placesForContacts(fc,
                                              place_type,
                                              woe_id, place_id, threshold,
                                              contacts,
                                              min_upload_date,
                                              max_upload_date,
                                              min_taken_date,
                                              max_taken_date);
  if(places) {
    int i;
    for(i = 0; places[i]; i++) {
      fprintf(stdout, "Place Result #%d\n", i);
      command_print_place(places[i], NULL, NULL, 0);
    }
    flickcurl_free_places(places);
  }

  tidy:
  return (places == NULL);
}
