grab_job(const char *cmd)
{
   QueueJob *j = jobs, *head = NULL, *tail = NULL;

   while(j) {
      QueueJob *match = get_next_match(cmd, j);
      if(!match) break;
      j = match->next;


      unlink_job(match);
      insert_jobs(match, head, tail, NULL);
   }

   return head;
}
