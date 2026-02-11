llist_print(llist_entry **llist)
{
   llist_entry *ei;

   for(ei = (*llist); ei != NULL; ei = ei->next)
      {
         printf("%s\n", (char *)ei->val);
      }
   return 0;
}
