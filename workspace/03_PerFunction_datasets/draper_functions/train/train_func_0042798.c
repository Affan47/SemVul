gegl_dot_add_node_and_dependencies (GString  *string,
                                    GeglNode *node)
{
  GeglDotVisitor *dot_visitor;
  GeglPad        *pad;
  gpointer        context_id = string;

  dot_visitor = g_object_new (GEGL_TYPE_DOT_VISITOR,
                              "id", context_id,
                              NULL);

  gegl_dot_visitor_set_string_to_append (dot_visitor,
                                         string);


  gegl_visitor_bfs_traverse (GEGL_VISITOR (dot_visitor),
                             GEGL_VISITABLE (node));


  pad = gegl_node_get_pad (node, "output");
  if (! pad)
    {
      pad = gegl_node_get_pad (node, "input");

      if (pad)
        {


          GSList *iter;
          for (iter = pad->connections; iter; iter = g_slist_next (iter))
            {
              GeglConnection *connection = iter->data;
              gegl_dot_util_add_connection (string, connection);
            }
        }
    }


  gegl_visitor_bfs_traverse (GEGL_VISITOR (dot_visitor),
                             GEGL_VISITABLE (pad));

  g_object_unref (dot_visitor);
}
