writeHeaders(void *ptr, size_t size,
				  size_t nmemb, void *stream)
{

  CMPIStatus *status=(CMPIStatus*)stream;
  char *str=ptr;
  char *colonidx;

  if (str[nmemb-1] != 0) {

      str = malloc(nmemb + 1);
      memcpy(str,ptr,nmemb);
      str[nmemb] = 0;
  } else {
    str = strdup(ptr);
  }
  colonidx=strchr(str,':');
  if (colonidx) {
    *colonidx=0;
    if (strcasecmp(str,"cimstatuscode") == 0) {

      status->rc = atoi(colonidx+1);
    } else {
      	if (strcasecmp(str, "cimstatuscodedescription") == 0) {
           status->msg=newCMPIString(colonidx+1,NULL);
      }
    }
  }
  free(str);
  return nmemb;
}
