getobjectbyname_nis(const char * name) {
 char           * cur, *next;
 char             proto[16];
 struct servent * se;
 static char    * search_order = NULL;

 if ( search_order == NULL ) {
  if ( (search_order = getenv(DNOBJ_SEARCH_ENV)) == NULL )
   search_order = DNOBJ_SEARCH_DEF;
  if ( !*search_order )
   search_order = DNOBJ_SEARCH_DEF;
 }

 cur = search_order;

 while (cur && *cur) {
  if ( (next = strstr(cur, " ")) == NULL ) {
   strncpy(proto, cur, 16);
  } else {
   strncpy(proto, cur, next-cur);
   proto[next-cur] = 0;
   next++;
  }
  cur = next;

  if ( (se = getservbyname(name, proto)) != NULL ) {
   return ntohs(se->s_port);
  }
 }

 errno = ENOENT;
 return -1;
}
