GetMandatoryValue( xmlNode * & node, const char * tag )
{
   xmlChar * value = NULL;

   while ( node != NULL ) {
      if ( node->type == XML_ELEMENT_NODE ) {
         if ( xmlStrcmp( node->name, BAD_CAST tag) == 0 ) {
            value = node->children->content;
            node = node->next;
            break;
         }
         return NULL;
      }
      node = node->next;
   }

   return value;
}
