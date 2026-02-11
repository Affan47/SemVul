mxml_write_subtree(MXML_WRITER *writer, rb::PMXML_NODE tree, int indent)
{
   int i;

   rb::mxml_start_element1(writer, tree->name, indent);
   for (i=0 ; i<tree->n_attributes ; i++)
      if (!mxml_write_attribute(writer, tree->attribute_name+i*MXML_NAME_LENGTH, tree->attribute_value[i]))
         return FALSE;

   if (tree->value)
      if (!mxml_write_value(writer, tree->value))
         return FALSE;

   for (i=0 ; i<tree->n_children ; i++)
      if (!mxml_write_subtree(writer, &tree->child[i], (tree->value == NULL) || i > 0))
         return FALSE;

   return rb::mxml_end_element(writer);
}
