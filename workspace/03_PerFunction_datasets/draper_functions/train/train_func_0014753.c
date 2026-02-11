_get_error_from_response                (xmlDoc *doc,
                                         FspErrorMethod error_method)
{
  RestResponseType rsp_type = REST_RESPONSE_UNKNOWN;
  GError *err = NULL;


  err = g_error_new_literal (FSP_ERROR, FSP_ERROR_OTHER, "Internal error");

  rsp_type = _get_response_type (doc);
  if (rsp_type == REST_RESPONSE_FAIL)
    {
      xmlNode *root = NULL;
      xmlNode *node = NULL;

      root = xmlDocGetRootElement (doc);
      if (root == NULL)
        return err;


      for (node = root->children; node != NULL; node = node->next)
        {
          if (node->type != XML_ELEMENT_NODE)
            continue;

          if (!g_strcmp0 ((gchar *) node->name, "err"))
            break;
        }

      if (node != NULL)
        {

          if (err)
            g_error_free (err);
          err = _parse_error_from_node (node, error_method);
        }
    }

  return err;
}
