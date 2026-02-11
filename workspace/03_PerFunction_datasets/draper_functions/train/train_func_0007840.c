do_autoprune(JCR *jcr)
{
   UAContext *ua;
   CLIENT *client;
   POOL *pool;
   bool pruned;

   if (!jcr->client) {
      return;
   }

   ua = new_ua_context(jcr);
   client = jcr->client;
   pool = jcr->pool;

   if (jcr->job->PruneJobs || jcr->client->AutoPrune) {
      prune_jobs(ua, client, pool, jcr->getJobType());
      pruned = true;
   } else {
      pruned = false;
   }

   if (jcr->job->PruneFiles || jcr->client->AutoPrune) {
      prune_files(ua, client, pool);
      pruned = true;
   }
   if (pruned) {
      Jmsg(jcr, M_INFO, 0, _("End auto prune.\n\n"));
   }
   free_ua_context(ua);
   return;
}
