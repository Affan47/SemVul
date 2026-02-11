mxml_add_attribute(rb::PMXML_NODE pnode, const char *attrib_name, const char *attrib_value)
{
   if (pnode->n_attributes == 0) {
      pnode->attribute_name  = (char*)mxml_malloc(MXML_NAME_LENGTH);
      pnode->attribute_value = (char**)mxml_malloc(sizeof(char *));
   } else {
      pnode->attribute_name  = (char*)mxml_realloc(pnode->attribute_name,  MXML_NAME_LENGTH*(pnode->n_attributes+1));
      pnode->attribute_value = (char**)mxml_realloc(pnode->attribute_value, sizeof(char *)*(pnode->n_attributes+1));
   }

   rb::strlcpy(pnode->attribute_name+pnode->n_attributes*MXML_NAME_LENGTH, attrib_name, MXML_NAME_LENGTH);
   pnode->attribute_value[pnode->n_attributes] = (char *)mxml_malloc(strlen(attrib_value)+1);
   strcpy(pnode->attribute_value[pnode->n_attributes], attrib_value);
   pnode->n_attributes++;

   return TRUE;
}
