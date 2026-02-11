gib_list_unlink(gib_list * root, gib_list * l)
{
   if (!l)
      return (root);

   if ((!root) || ((l == root) && (!l->next)))
      return (NULL);

   if (l->prev)
      l->prev->next = l->next;
   if (l->next)
      l->next->prev = l->prev;
   if (root == l)
      root = root->next;
   return (root);
}
