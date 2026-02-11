get_next_match(const char *cmd, QueueJob *j)
{
   while(j) {
      if(!fnmatch(cmd, j->cmd,FNM_CASEFOLD))
	 return j;

      j = j->next;
   }
   return 0;
}
