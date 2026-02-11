get_sockaddr(value mladr,
                  union sock_addr_union * adr ,
                  socklen_param_type * adr_len )
{
  switch(Tag_val(mladr)) {
#ifndef _WIN32
  case 0:
    { value path;
      mlsize_t len;
      path = Field(mladr, 0);
      len = string_length(path);
      adr->s_unix.sun_family = AF_UNIX;
      if (len >= sizeof(adr->s_unix.sun_path)) {
        unix_error(ENAMETOOLONG, "", path);
      }
      memmove (adr->s_unix.sun_path, String_val(path), len + 1);
      *adr_len =
        ((char *)&(adr->s_unix.sun_path) - (char *)&(adr->s_unix))
        + len;
      break;
    }
#endif
  case 1:
#ifdef HAS_IPV6
    if (string_length(Field(mladr, 0)) == 16) {
      memset(&adr->s_inet6, 0, sizeof(struct sockaddr_in6));
      adr->s_inet6.sin6_family = AF_INET6;
      adr->s_inet6.sin6_addr = GET_INET6_ADDR(Field(mladr, 0));
      adr->s_inet6.sin6_port = htons(Int_val(Field(mladr, 1)));
#ifdef SIN6_LEN
      adr->s_inet6.sin6_len = sizeof(struct sockaddr_in6);
#endif
      *adr_len = sizeof(struct sockaddr_in6);
      break;
    }
#endif
    memset(&adr->s_inet, 0, sizeof(struct sockaddr_in));
    adr->s_inet.sin_family = AF_INET;
    adr->s_inet.sin_addr = GET_INET_ADDR(Field(mladr, 0));
    adr->s_inet.sin_port = htons(Int_val(Field(mladr, 1)));
#ifdef SIN6_LEN
    adr->s_inet.sin_len = sizeof(struct sockaddr_in);
#endif
    *adr_len = sizeof(struct sockaddr_in);
    break;
  }
}
