dec_outstanding (GstBufferPool * pool)
{
  if (g_atomic_int_dec_and_test (&pool->priv->outstanding)) {

    if (GST_BUFFER_POOL_IS_FLUSHING (pool)) {

      GST_BUFFER_POOL_LOCK (pool);


      if (GST_BUFFER_POOL_IS_FLUSHING (pool))
        do_stop (pool);

      GST_BUFFER_POOL_UNLOCK (pool);
    }
  }
}
