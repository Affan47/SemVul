so_create(char *name,void *data,size_t len)
{
   struct store_object *so;

   if (!(so = malloc(sizeof(*so))))
      return NULL;

   if (!(so->name = strdup(name)))
      goto err_name;

   so->data = data;
   so->len  = len;

   if (registry_add(so->name,OBJ_TYPE_STORE,so) == -1)
      goto err_registry;

   return so;

 err_registry:
   free(so->name);
 err_name:
   free(so);
   return NULL;
}
