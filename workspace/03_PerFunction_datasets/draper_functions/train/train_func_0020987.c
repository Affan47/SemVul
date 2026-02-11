pool_reset(POOL *pool)
{


	obstack_free(&pool->obstack, pool->first_object);
}
