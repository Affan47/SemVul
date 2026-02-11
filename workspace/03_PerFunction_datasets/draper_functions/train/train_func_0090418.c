glade_project_write_comments (GladeProject *project,
                             GladeXmlDoc  *doc,
                             GladeXmlNode *root)
{
  GladeProjectPrivate *priv = project->priv;
  GladeXmlNode *comment_node;
  GList *l;

    comment_node = glade_xml_doc_new_comment (doc, GLADE_PROJECT_COMMENT);
  comment_node = glade_xml_node_add_prev_sibling (root, comment_node);

  for (l = priv->comments; l; l = g_list_next (l))
    {
      gchar *comment = l->data;
      GladeXmlNode *node;

      node = glade_xml_doc_new_comment (doc, comment);
      comment_node = glade_xml_node_add_next_sibling (comment_node, node);
    }
}
