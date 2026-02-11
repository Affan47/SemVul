clutter_path_parse_description (const gchar  *p,
                                GSList      **ret)
{
  ClutterPathNodeFull *node;
  GSList *nodes = NULL;

  if (p == NULL || *p == '\0')
    return FALSE;

  while (TRUE)
    {

      while (clutter_path_isspace (*p))
        p++;


      if (*p == '\0')
        break;

      switch (*p)
        {
        case 'M':
        case 'm':
        case 'L':
        case 'l':
          node = clutter_path_node_full_new ();
          nodes = g_slist_prepend (nodes, node);

          node->k.type = (*p == 'M' ? CLUTTER_PATH_MOVE_TO :
                          *p == 'm' ? CLUTTER_PATH_REL_MOVE_TO :
                          *p == 'L' ? CLUTTER_PATH_LINE_TO :
                          CLUTTER_PATH_REL_LINE_TO);
          p++;

          if (!clutter_path_parse_number (&p, FALSE, &node->k.points[0].x) ||
              !clutter_path_parse_number (&p, TRUE, &node->k.points[0].y))
            goto fail;
          break;

        case 'C':
        case 'c':
          node = clutter_path_node_full_new ();
          nodes = g_slist_prepend (nodes, node);

          node->k.type = (*p == 'C' ? CLUTTER_PATH_CURVE_TO :
                          CLUTTER_PATH_REL_CURVE_TO);
          p++;

          if (!clutter_path_parse_number (&p, FALSE, &node->k.points[0].x) ||
              !clutter_path_parse_number (&p, TRUE, &node->k.points[0].y) ||
              !clutter_path_parse_number (&p, TRUE, &node->k.points[1].x) ||
              !clutter_path_parse_number (&p, TRUE, &node->k.points[1].y) ||
              !clutter_path_parse_number (&p, TRUE, &node->k.points[2].x) ||
              !clutter_path_parse_number (&p, TRUE, &node->k.points[2].y))
            goto fail;
          break;

        case 'Z':
        case 'z':
          node = clutter_path_node_full_new ();
          nodes = g_slist_prepend (nodes, node);
          p++;

          node->k.type = CLUTTER_PATH_CLOSE;
          break;

        default:
          goto fail;
        }
    }

  *ret = g_slist_reverse (nodes);
  return TRUE;

 fail:
  g_slist_foreach (nodes, (GFunc) clutter_path_node_full_free, NULL);
  g_slist_free (nodes);
  return FALSE;
}
