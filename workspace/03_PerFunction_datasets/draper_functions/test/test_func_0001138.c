sge_dstring_allocate(dstring *sb, size_t request)
{

   size_t chunks = request / REALLOC_CHUNK + 1;
   request = chunks * REALLOC_CHUNK;


   sb->size += request;


   if (sb->s != NULL) {
      sb->s = sge_realloc(sb->s, sb->size * sizeof(char), 1);
   } else {
      sb->s = malloc(sb->size * sizeof(char));
      sb->s[0] = '\0';
   }
}
