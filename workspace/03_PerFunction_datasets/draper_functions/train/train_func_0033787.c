cluster_dead_hosts_sort( llist_entry *a, llist_entry *b )
{
   double ai, bi;

   ai = ((gexec_host_t*)(a->val))->last_reported;
   bi = ((gexec_host_t*)(b->val))->last_reported;

   if (ai<bi) return 1;
   return 0;
}
