mp_create_fixed_pool(mempool_t *mp,char *name)
{
   memset(mp,0,sizeof(*mp));

   if (pthread_mutex_init(&mp->lock,NULL) != 0)
      return NULL;

   mp->name = name;
   mp->block_list = NULL;
   mp->flags = MEMPOOL_FIXED;
   return mp;
}
