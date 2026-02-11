netio_create(char *name)
{
   netio_desc_t *nio;

   if (!(nio = malloc(sizeof(*nio))))
      return NULL;


   memset(nio,0,sizeof(*nio));
   nio->type = NETIO_TYPE_NULL;


   if (!(nio->name = strdup(name))) {
      free(nio);
      return NULL;
   }

   return nio;
}
