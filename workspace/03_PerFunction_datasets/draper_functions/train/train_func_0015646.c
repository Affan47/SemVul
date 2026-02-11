command_activity_userPhotos(flickcurl* fc, int argc, char *argv[])
{
  char* timeframe = argv[1];
  int per_page = 10;
  int page = 0;
  flickcurl_activity** activities = NULL;
  int i;

  if(argc >2) {
    per_page = parse_page_param(argv[2]);
    if(argc >3) {
      page = parse_page_param(argv[3]);
    }
  }

  activities = flickcurl_activity_userPhotos(fc, timeframe, per_page, page);
  if(!activities)
    return 1;

  if(verbose)
    fprintf(stdout,
            "%s: Recent activity on the caller's photos (timeframe %s  per_page %d  page %d):\n",
            program, timeframe, per_page, page);
  for(i = 0; activities[i]; i++) {
    fprintf(stdout, "%s: Activity %d\n", program, i);
    command_print_activity(activities[i]);
  }

  flickcurl_free_activities(activities);

  return 0;
}
