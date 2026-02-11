new_part(Mime_part *omp)
{
  Mime_part *mp;

  if (omp == NULL)
	mp = ALLOC(Mime_part);
  else
	mp = omp;

  mp->version = NULL;
  mp->type = new_content_type(NULL);
  mp->encoding = MIME_ENCODING_7BIT;
  mp->disposition = NULL;
  mp->format = MIME_FORMAT_UNKNOWN;
  mp->content_id = NULL;
  mp->description = NULL;
  mp->body = NULL;
  mp->truncated = 0;
  mp->decoded = 0;
  mp->next = NULL;

  return(mp);
}
