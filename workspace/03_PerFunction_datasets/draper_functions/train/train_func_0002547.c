NonFatalError(int err)
{
   if(E_RETRY(err))
      return true;

   current->TimeoutS(1);
   if(err==ENFILE || err==EMFILE)
      return true;
#ifdef ENOBUFS
   if(err==ENOBUFS)
      return true;
#endif
#ifdef ENOSR
   if(err==ENOSR)
      return true;
#endif
#ifdef ENOSPC
   if(err==ENOSPC)
      return !enospc_fatal.QueryBool(0);
#endif
#ifdef EDQUOT
   if(err==EDQUOT)
      return !enospc_fatal.QueryBool(0);
#endif

   current->Timeout(0);
   return false;
}
