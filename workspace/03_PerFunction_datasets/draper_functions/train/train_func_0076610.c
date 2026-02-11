headers_callback(void *ptr, size_t size, size_t nmemb, void *p)


{
  float f;
  char  *s, *q;
  size_t realsize;
  struct tm modified_tm;
  struct grst_header_data *header_data;

  header_data = (struct grst_header_data *) p;
  realsize = size * nmemb;
  s = malloc(realsize + 1);
  memcpy(s, ptr, realsize);
  s[realsize] = '\0';

  if      (sscanf(s, "Content-Length: %d", &(header_data->length)) == 1)
            header_data->length_set = 1;
  else if (sscanf(s, "HTTP/%f %d ", &f, &(header_data->retcode)) == 2) ;
  else if (strncmp(s, "Location: ", 10) == 0)
      {
        header_data->location = strdup(&s[10]);

        for (q=header_data->location; *q != '\0'; ++q)
         if ((*q == '\r') || (*q == '\n')) *q = '\0';

        if (header_data->common_data->verbose > 0)
             fprintf(stderr, "Received Location: %s\n", header_data->location);
      }
  else if (strncmp(s, "Set-Cookie: GRIDHTTP_PASSCODE=", 29) == 0)
      {
        header_data->gridhttppasscode = strdup(&s[12]);
        q = index(header_data->gridhttppasscode, ';');
        if (q != NULL) *q = '\0';

        if (header_data->common_data->verbose > 0)
             fprintf(stderr, "Received GridHTTP Auth Cookie: %s\n",
                             header_data->gridhttppasscode);
      }
  else if (strncmp(s, "Last-Modified: ", 15) == 0)
      {


        if (strptime(&s[15], "%a, %d %b %Y %T GMT", &modified_tm) != NULL)
          {
            header_data->modified = mktime(&modified_tm);
            header_data->modified_set = 1;
          }
        else if (strptime(&s[15], "%a, %d-%b-%y %T GMT", &modified_tm) != NULL)
          {
            header_data->modified = mktime(&modified_tm);
            header_data->modified_set = 1;
          }
        else if (strptime(&s[15], "%a %b %d %T %Y", &modified_tm) != NULL)
          {
            header_data->modified = mktime(&modified_tm);
            header_data->modified_set = 1;
          }
      }

  free(s);
  return realsize;
}
