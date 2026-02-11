prep_addr (char * buf, char * object) {
 struct nodeent * ne;

 *index(buf, '/') = 0;

  if ( strcmp(buf, "0.0") == 0 && ! numeric ) {
   strcpy(buf, "*");
  } else if ( !numeric ) {
   if ( (ne = getnodebyname(buf)) != NULL ) {
    if ( (ne = getnodebyaddr((const char *)ne->n_addr, ne->n_length, ne->n_addrtype)) != NULL ) {
     strcpy(buf, ne->n_name);
    }
   }
  }

 strcat(buf, "::");

 if ( strcmp(object, "0") == 0 && ! numeric ) {
  strcat(buf, "*");
 } else {
  strcat(buf, object_name(object));
 }
 return 0;
}
