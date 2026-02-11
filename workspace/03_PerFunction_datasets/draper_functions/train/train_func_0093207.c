command_photos_comments_addComment(flickcurl* fc, int argc, char *argv[])
{
  const char *photo_id = argv[1];
  const char *comment_text = argv[2];
  char* id;

  id = flickcurl_photos_comments_addComment(fc, photo_id, comment_text);
  if(id) {
    fprintf(stdout,
            "%s: Added comment '%s' to photo %s giving comment ID %s\n",
            program, photo_id, comment_text, id);
  }

  return (id == NULL);
}
