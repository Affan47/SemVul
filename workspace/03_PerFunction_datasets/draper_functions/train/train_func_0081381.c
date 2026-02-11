gib_list_add_front(gib_list * root, void *data)
{
   gib_list *l;

   l = gib_list_new();
   l->next = root;
   l->data = data;
   if (root)
      root->prev = l;
   return (l);
}
