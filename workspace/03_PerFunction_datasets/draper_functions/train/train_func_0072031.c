command_short_uri(flickcurl* fc, int argc, char *argv[])
{
  char *photo_id = argv[1];
  char *uri;

  uri = flickcurl_photo_id_as_short_uri(photo_id);
  if(uri) {
    fprintf(stdout, "%s: Short URI for photo ID %s is %s\n",
            program, photo_id, uri);
    free(uri);
  } else {
    fprintf(stderr, "%s: Failed to get short URI for photo ID %s\n",
            program, photo_id);
    return 1;
  }
  return 0;

}
