read_xml_file(char *fname)
{

  xmlDocPtr  doc;

  g_return_val_if_fail(fname!=NULL,FALSE);


  doc = xmlParseFile(fname);

  if(!doc)
    return FALSE;

  if(
     !doc->children ||

     !doc->children->name ||

     g_ascii_strcasecmp((char *)doc->children->name, "ShapeGame")!=0) {
    xmlFreeDoc(doc);
    return FALSE;
  }


  shapeBox.x = xmlGetProp_Double(doc->children, BAD_CAST "shapebox_x", 15);

  shapeBox.y = xmlGetProp_Double(doc->children, BAD_CAST "shapebox_y", 25);

  shapeBox.w = xmlGetProp_Double(doc->children, BAD_CAST "shapebox_w", 80);

  shapeBox.h = xmlGetProp_Double(doc->children, BAD_CAST "shapebox_h", 430);

  shapeBox.nb_shape_x = xmlGetProp_Double(doc->children, BAD_CAST "shapebox_nb_shape_x", 1);

  shapeBox.nb_shape_y = xmlGetProp_Double(doc->children, BAD_CAST "shapebox_nb_shape_y", 5);


  shadow_enable = xmlGetProp_Double(doc->children, BAD_CAST "shadow_enable", 1);


  parse_doc(doc);

  xmlFreeDoc(doc);

  return TRUE;
}
