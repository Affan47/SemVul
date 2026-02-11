open_bootstrap_file(JCR *jcr, bootstrap_info &info)
{
   FILE *bs;
   UAContext *ua;
   info.bs = NULL;
   info.ua = NULL;

   if (!jcr->RestoreBootstrap) {
      return false;
   }
   strncpy(info.storage, jcr->rstore->name(), MAX_NAME_LENGTH);

   bs = fopen(jcr->RestoreBootstrap, "rb");
   if (!bs) {
      berrno be;
      Jmsg(jcr, M_FATAL, 0, _("Could not open bootstrap file %s: ERR=%s\n"),
         jcr->RestoreBootstrap, be.bstrerror());
      jcr->setJobStatus(JS_ErrorTerminated);
      return false;
   }

   ua = new_ua_context(jcr);
   ua->cmd = check_pool_memory_size(ua->cmd, UA_CMD_SIZE+1);
   while (!fgets(ua->cmd, UA_CMD_SIZE, bs)) {
      parse_ua_args(ua);
      if (ua->argc != 1) {
         continue;
      }
      if (!strcasecmp(ua->argk[0], "Storage")) {
         strncpy(info.storage, ua->argv[0], MAX_NAME_LENGTH);
         break;
      }
   }
   info.bs = bs;
   info.ua = ua;
   fseek(bs, 0, SEEK_SET);
   return true;
}
