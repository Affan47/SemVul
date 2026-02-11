info_handle_pointer (char *label, WINDOW *window)
{
  if (info_parsed_filename || info_parsed_nodename)
    {
      char *filename, *nodename;
      NODE *node;

      filename = nodename = NULL;

      if (info_parsed_filename)
        filename = xstrdup (info_parsed_filename);
      else
        {
          if (window->node->parent)
            filename = xstrdup (window->node->parent);
          else if (window->node->filename)
            filename = xstrdup (window->node->filename);
        }

      if (info_parsed_nodename)
        nodename = xstrdup (info_parsed_nodename);
      else
        nodename = xstrdup ("Top");

      node = info_get_node (filename, nodename, PARSE_NODE_DFLT);

      if (node)
        {
          INFO_WINDOW *info_win;

          info_win = get_info_window_of_window (window);
          if (info_win)
            {
	      if (strcmp (label, "Up") == 0)
		{
		  int i = info_win_find_node (info_win, node);
		  if (i >= 0)
		    node->display_pos = info_win->points[i];
		}
	      info_win->pagetops[info_win->current] = window->pagetop;
              info_win->points[info_win->current] = window->point;
            }
          info_set_node_of_window (1, window, node);
        }
      else
        {
          if (info_recent_file_error)
            info_error ("%s", info_recent_file_error);
          else
            info_error (msg_cant_file_node, filename, nodename);
        }

      free (filename);
      free (nodename);
    }
  else
    {
      info_error (msg_no_pointer, label);
    }
}
