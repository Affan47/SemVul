cc_xml_elt_get_data(const cc_xml_elt * elt)
{
  if ( strcmp(elt->type, COIN_XML_CDATA_TYPE) != 0 ) {
    if ( (cc_xml_elt_get_num_children(elt) == 1) &&
         (strcmp(elt->children[0]->type, COIN_XML_CDATA_TYPE) == 0) ) {
      return elt->children[0]->data;
    }
  }
  return elt->data;
}
