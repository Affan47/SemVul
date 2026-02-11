parse_doc(xmlDocPtr doc)
{
  GList *shape_list_init = NULL;
  xmlNodePtr node;
  GooCanvasItem *item;


  for(node = doc->children->children; node != NULL; node = node->next) {


    add_xml_shape_to_data(doc, node, NULL, &shape_list_init);
  }

  shape_list = g_list_copy(shape_list_init);
  insert_shape_random(shape_list_init, 0xFF ^ SHAPE_BACKGROUND);
  insert_shape_sequence(shape_list_init, SHAPE_BACKGROUND);
  g_list_free(shape_list_init);
  shape_list_init = NULL;

  if(current_shapelistgroup_index > 0)
    {
      item = g_list_nth_data(shape_list_group, current_shapelistgroup_index);
      g_object_set (item, "visibility", GOO_CANVAS_ITEM_INVISIBLE, NULL);
      item = g_list_nth_data(shape_list_group, 0);
      g_object_set (item, "visibility", GOO_CANVAS_ITEM_VISIBLE, NULL);
      g_object_set (previous_shapelist_item, "visibility", GOO_CANVAS_ITEM_INVISIBLE, NULL);
      g_object_set (next_shapelist_item, "visibility", GOO_CANVAS_ITEM_VISIBLE, NULL);
      current_shapelistgroup_index = 0;
    }
}
