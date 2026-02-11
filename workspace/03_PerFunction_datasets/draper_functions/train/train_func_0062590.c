command_photosets_comments_addComment(flickcurl* fc, int argc, char *argv[])
{
  const char *photoset_id = argv[1];
  const char *comment_text = argv[2];
  char* id;

  id = flickcurl_photosets_comments_addComment(fc, photoset_id, comment_text);
  if(id) {
    fprintf(stdout,
            "%s: Added comment '%s' to photoset %s giving comment ID %s\n",
            program, photoset_id, comment_text, id);
    free(id);
  }

  return (id == NULL);
}
