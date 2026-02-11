_remove(entry **ep)
{
   if(!ep || !*ep)
      return;
   entry *e=*ep;
   *ep=e->next;
   delete e;
   entry_count--;
}
