_eina_share_common_head_remove_node(Eina_Share_Common_Head *head,
                                    const Eina_Share_Common_Node *node)
{
   Eina_Share_Common_Node *cur, *prev;

   if (head->head == node)
     {
        head->head = node->next;
        return 1;
     }

   prev = head->head;
   cur = head->head->next;
   for (; cur; prev = cur, cur = cur->next)
      if (cur == node)
        {
           prev->next = cur->next;
           return 1;
        }

   return 0;
}
