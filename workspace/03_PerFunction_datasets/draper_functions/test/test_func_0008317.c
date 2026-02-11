_eina_simple_xml_node_data_new(Eina_Simple_XML_Node_Tag *parent, Eina_Simple_XML_Node_Type type, const char *content, unsigned length)
{
   Eina_Simple_XML_Node_Data *n;

   if (!content) return NULL;

   n = malloc(sizeof(*n) + length + 1);

   if (!n)
     {
        ERR("could not allocate memory for node");
        return NULL;
     }

   EINA_MAGIC_SET(&n->base, EINA_MAGIC_SIMPLE_XML_DATA);
   n->base.type = type;
   n->base.parent = parent;

   n->length = length;
   memcpy(n->data, content, length);
   n->data[length] = '\0';

   if (parent)
     parent->children = eina_inlist_append
       (parent->children, EINA_INLIST_GET(&n->base));

   return n;
}
