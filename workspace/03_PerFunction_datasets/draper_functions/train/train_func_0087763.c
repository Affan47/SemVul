_eio_pool_malloc(Eio_Alloc_Pool *pool, size_t sz)
{
   void *result = NULL;

   if (pool->count)
     {
        EIO_MUTEX_LOCK(pool);
        result = eina_trash_pop(&pool->trash);
        if (result) pool->count--;
        EIO_MUTEX_UNLOCK(pool);
     }

   if (!result) result = malloc(sz);
   return result;
}
