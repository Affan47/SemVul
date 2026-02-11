thread_pool_routine(void *dt)
{
   struct ipcache_item *curitem;
   struct ipresolve_link *el;
   struct hostent resultbuf;
   struct hostent *resultptr;
   char extrabuf[4096];
   int errnovar;
   int result;

   while (!request_stop_thread)
   {
      pthread_mutex_lock(&resolvemtx);

      if (!request_stop_thread && !resolveListHead)
      {

         pthread_cond_wait (&resolvecond, &resolvemtx);
      }


      if (request_stop_thread)
      {

         pthread_mutex_unlock(&resolvemtx);
         break;
      }


      if (resolveListHead)
      {

         el = resolveListHead;
         resolveListHead = el->next;
         curitem = el->itemToResolve;


         pthread_mutex_unlock(&resolvemtx);

         free(el);

#ifdef FORCE_SINGLE_THREAD

         result=0;
         resultptr = gethostbyaddr (&curitem->ip.addr8,
                          address_len(curitem->ip.type), curitem->ip.type);
#else

         result = gethostbyaddr_r (&curitem->ip.addr8,
                          address_len(curitem->ip.type), curitem->ip.type,
                          &resultbuf, extrabuf, sizeof(extrabuf),
                          &resultptr, &errnovar);
         if (result != 0 && errnovar == ERANGE)
            g_my_critical("Insufficient memory allocated to gethostbyaddr_r\n");
#endif
         if (request_stop_thread)
            break;


         pthread_mutex_lock(&resolvemtx);
         if (result || !resultptr)
            ipcache_request_failed(curitem);
         else
            ipcache_request_succeeded(curitem, 3600L*24L, resultptr->h_name);
      }

      pthread_mutex_unlock(&resolvemtx);
   }
   return NULL;
}
