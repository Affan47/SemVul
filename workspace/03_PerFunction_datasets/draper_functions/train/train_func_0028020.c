mxml_delete_node(rb::PMXML_NODE pnode)
{
   rb::PMXML_NODE parent;
   int i, j;


   parent = pnode->parent;

   if (parent) {
      for (i=0 ; i<parent->n_children ; i++)
         if (&parent->child[i] == pnode)
            break;


      rb::mxml_free_tree(pnode);

      if (i < parent->n_children) {
         for (j=i ; j<parent->n_children-1 ; j++)
            memcpy(&parent->child[j], &parent->child[j+1], sizeof(MXML_NODE));
         parent->n_children--;
         if (parent->n_children)
            parent->child = (rb::PMXML_NODE)mxml_realloc(parent->child, sizeof(MXML_NODE)*(parent->n_children));
         else
            rb::mxml_free(parent->child);
      }
   } else
      rb::mxml_free_tree(pnode);

   return TRUE;
}
