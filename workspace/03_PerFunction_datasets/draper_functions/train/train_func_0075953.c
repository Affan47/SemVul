set_rwstorage(JCR *jcr, USTORE *store)
{
   if (!store) {
      Jmsg(jcr, M_FATAL, 0, _("No storage specified.\n"));
      return;
   }
   if (jcr->JobReads()) {
      set_rstorage(jcr, store);
   }
   set_wstorage(jcr, store);
}
