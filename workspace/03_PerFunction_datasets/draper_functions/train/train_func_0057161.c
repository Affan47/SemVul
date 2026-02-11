freednsentry(void *freethis)
{
  struct Curl_dns_entry *p = (struct Curl_dns_entry *) freethis;


  p->timestamp = 0;
  if(p->inuse == 0) {
    Curl_freeaddrinfo(p->addr);
    free(p);
  }
}
