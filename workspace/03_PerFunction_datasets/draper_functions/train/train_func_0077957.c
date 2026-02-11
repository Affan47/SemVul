eina_simple_xml_node_cdata_free(Eina_Simple_XML_Node_Data *node)
{
   if (!node)
     return;

   EINA_MAGIC_CHECK_DATA(&node->base);
   if (node->base.type != EINA_SIMPLE_XML_NODE_CDATA)
     {
        ERR("expected node of type: cdata!");
        return;
     }
   _eina_simple_xml_node_data_free(node);
}
