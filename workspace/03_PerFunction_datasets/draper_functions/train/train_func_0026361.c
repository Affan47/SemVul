evas_cache_engine_image_init(const Evas_Cache_Engine_Image_Func *cb, Evas_Cache_Image *parent)
{
   Evas_Cache_Engine_Image     *new;

   new = malloc(sizeof (Evas_Cache_Engine_Image));
   if (!new)
     return NULL;

   new->func = *cb;

   new->limit = 0;
   new->usage = 0;

   new->dirty = NULL;
   new->lru = NULL;
   new->activ = eina_hash_string_superfast_new(NULL);
   new->inactiv = eina_hash_string_superfast_new(NULL);

   new->parent = parent;
   parent->references++;

   new->brother = NULL;

   return new;
}
