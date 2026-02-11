localgetpwnam(struct s_localpwd *localpwd, char *username) {
   int i;
   size_t len;

   for (i=0; i<(localpwd->numentries);i++) {
      len = (strlen(username)>29)?30:strlen(username)+1;
      if (!memcmp(username,localpwd->uname[i],len)) {
	return &(localpwd->uid[i]);
      }
   }
   return NULL;
}
