command_contacts_getListRecentlyUploaded(flickcurl* fc, int argc, char *argv[])
{
  flickcurl_contact **contacts = NULL;
  int date_lastupload = 1;
  const char* filter = NULL;

  if(argc >1) {
    date_lastupload = atoi(argv[1]);
    if(argc >2) {
      filter = argv[2];
    }
  }

  contacts = flickcurl_contacts_getListRecentlyUploaded(fc, date_lastupload,
                                                        filter);
  if(contacts) {
    int i;
    for(i = 0; contacts[i]; i++)
      command_print_contact(contacts[i], i);

    flickcurl_free_contacts(contacts);
  }

  return (contacts == NULL);
}
