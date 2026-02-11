glade_project_read_requires (GladeProject *project,
                             GladeXmlNode *root_node,
                             const gchar *path, gboolean *has_gtk_dep)
{

  GString *string = g_string_new (NULL);
  GladeXmlNode *node;
  gchar *required_lib = NULL;
  gboolean loadable = TRUE;
  guint16 major, minor;
  gint position = 0;

  for (node = glade_xml_node_get_children_with_comments (root_node);
       node; node = glade_xml_node_next_with_comments (node))
    {

      if (!(glade_xml_node_verify_silent (node, GLADE_XML_TAG_REQUIRES) ||
            (required_lib =
             glade_project_read_requires_from_comment (node, &major, &minor))))
        continue;

      if (!required_lib)
        {
          required_lib =
              glade_xml_get_property_string_required (node, GLADE_XML_TAG_LIB,
                                                      NULL);
          glade_xml_get_property_version (node, GLADE_XML_TAG_VERSION,
                                          &major, &minor);
        }

      if (!required_lib)
        continue;


      if (!glade_catalog_is_loaded (required_lib))
        {
          CatalogInfo *data = g_new0(CatalogInfo, 1);

          data->catalog = required_lib;
          data->position = position;


          project->priv->unknown_catalogs = g_list_append (project->priv->unknown_catalogs,
                                                           data);

          glade_project_set_target_version (project, required_lib, major, minor);

          if (!loadable)
            g_string_append (string, ", ");

          g_string_append (string, required_lib);
          loadable = FALSE;
        }
      else
        {
          if (has_gtk_dep && strcmp (required_lib, "gtk+") == 0)
            *has_gtk_dep = TRUE;

          glade_project_set_target_version
              (project, required_lib, major, minor);
          g_free (required_lib);
        }

      position++;
    }

  if (!loadable)
    glade_util_ui_message (glade_app_get_window (),
                           GLADE_UI_ERROR, NULL,
                           _("Failed to load %s.\n"
                             "The following required catalogs are unavailable: %s"),
                           path, string->str);
  g_string_free (string, TRUE);
  return loadable;
}
