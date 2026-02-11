command_photos_comments_getList(flickcurl* fc, int argc, char *argv[])
{
  const char *photo_id = argv[1];
  flickcurl_comment** comments;

  comments = flickcurl_photos_comments_getList(fc, photo_id);
  if(!comments)
    return 1;

  command_print_comments(comments, "Photo ID", photo_id);

  flickcurl_free_comments(comments);
  return 0;
}
