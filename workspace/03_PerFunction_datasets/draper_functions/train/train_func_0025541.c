getAttr(const char* data, const char* attr, char** val, char seperator)
{
  char* start;
  if ((start = strstr(data, attr)) != NULL) {
    char* end;
    int len;

    end = strchr(start, seperator);
    if (end == NULL) {
      end = start + strlen(start);
    }

    len = end-start - strlen(attr);

    *val = (char*) xcalloc(len+1, 1);
    memcpy(*val, start+strlen(attr), len);
    (*val)[len] = '\0';
  } else {
    *val = (char*) xcalloc(1, 1);
    (*val)[0] = '\0';
  }
}
