ftio_set_comment(struct ftio *ftio, char *comment)
{

  if (!comment)
    return 0;

  if (ftio->fth.comments)
    free(ftio->fth.comments);

  if (!(ftio->fth.comments = (char*)malloc(strlen(comment)+1))) {
    fterr_warn("malloc()");
    return -1;
  }
  strcpy(ftio->fth.comments, comment);
  ftio->fth.fields |= FT_FIELD_COMMENTS;
  return 0;
}
