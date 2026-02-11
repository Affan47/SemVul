mxml_clone_tree(rb::PMXML_NODE tree)
{
   rb::PMXML_NODE clone;
   int i;

   clone = (rb::PMXML_NODE)calloc(sizeof(MXML_NODE), 1);


   memcpy(clone, tree, sizeof(MXML_NODE));

   clone->value = NULL;
   rb::mxml_replace_node_value(clone, tree->value);

   clone->attribute_name = NULL;
   clone->attribute_value = NULL;
   for (i=0 ; i<tree->n_attributes ; i++)
      rb::mxml_add_attribute(clone, tree->attribute_name+i*rb::MXML_NAME_LENGTH, tree->attribute_value[i]);

   clone->child = NULL;
   clone->n_children = 0;
   for (i=0 ; i<tree->n_children ; i++)
      rb::mxml_add_tree(clone, rb::mxml_clone_tree(mxml_subnode(tree, i)));

   return clone;
}
