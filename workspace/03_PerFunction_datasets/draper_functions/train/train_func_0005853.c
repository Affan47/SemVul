eina_mempool_del(Eina_Mempool *mp)
{
   EINA_SAFETY_ON_NULL_RETURN(mp);
   EINA_SAFETY_ON_NULL_RETURN(mp->backend.shutdown);
   DBG("mp=%p", mp);
   mp->backend.shutdown(mp->backend_data);
   free(mp->backend2);
   free(mp);
}
