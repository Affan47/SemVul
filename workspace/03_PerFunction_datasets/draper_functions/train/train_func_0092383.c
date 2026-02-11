send_bootstrap_file(JCR *jcr, BSOCK *sd)
{
   FILE *bs;
   char buf[1000];
   const char *bootstrap = "bootstrap\n";

   Dmsg1(400, "send_bootstrap_file: %s\n", jcr->RestoreBootstrap);
   if (!jcr->RestoreBootstrap) {
      return true;
   }
   bs = fopen(jcr->RestoreBootstrap, "rb");
   if (!bs) {
      berrno be;
      Jmsg(jcr, M_FATAL, 0, _("Could not open bootstrap file %s: ERR=%s\n"),
         jcr->RestoreBootstrap, be.bstrerror());
      jcr->setJobStatus(JS_ErrorTerminated);
      return false;
   }
   sd->fsend(bootstrap);
   while (fgets(buf, sizeof(buf), bs)) {
      sd->fsend("%s", buf);
   }
   sd->signal(BNET_EOD);
   fclose(bs);
   if (jcr->unlink_bsr) {
      unlink(jcr->RestoreBootstrap);
      jcr->unlink_bsr = false;
   }
   return true;
}
