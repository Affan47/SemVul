eina_share_common_length(__UNUSED__ Eina_Share *share, const char *str)
{
   const Eina_Share_Common_Node *node;

   if (!str)
      return -1;

   node = _eina_share_common_node_from_str(str, share->node_magic);
   if (!node) return 0;
   return node->length;
}
