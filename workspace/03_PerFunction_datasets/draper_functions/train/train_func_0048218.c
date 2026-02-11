flickcurl_invoke_get_content(flickcurl *fc, size_t* size_p)
{
  char* content = NULL;
  if(!flickcurl_invoke_common(fc, &content, size_p, NULL))
    return content;
  return NULL;
}
