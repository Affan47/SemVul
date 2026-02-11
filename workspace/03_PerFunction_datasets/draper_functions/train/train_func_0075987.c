command_people_getGroups(flickcurl* fc, int argc, char *argv[])
{
  char* user_id = argv[1];
  flickcurl_group** groups = NULL;
  const char* extras = NULL;
  int i;

  groups = flickcurl_people_getGroups(fc, user_id, extras);
  if(!groups)
    return 1;

  for(i = 0; groups[i]; i++) {
    fprintf(stdout, "%s: Group %d\n", program, i);
    command_print_group(groups[i]);
  }

  flickcurl_free_groups(groups);

  return 0;
}
