_eina_share_common_head_alloc(int slen)
{
   Eina_Share_Common_Head *head;
   const size_t head_size = offsetof(Eina_Share_Common_Head, builtin_node.str);

   head = malloc(head_size + slen);
   if (!head)
      eina_error_set(EINA_ERROR_OUT_OF_MEMORY);

   return head;
}
