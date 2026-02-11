backward_move_node_structure (WINDOW *window, int behaviour)
{
  switch (behaviour)
    {
    case IS_PageOnly:
      info_error ("%s", msg_at_node_top);
      return 1;

    case IS_NextOnly:
      info_prev_label_of_node (window->node);
      if (!info_parsed_nodename && !info_parsed_filename)
        {
          info_error ("%s", _("No `Prev' for this node."));
          return 1;
        }
      else
        {
          info_handle_pointer ("Prev", window);
        }
      break;

    case IS_Continuous:
      info_prev_label_of_node (window->node);

      if (!info_parsed_nodename && (!info_parsed_filename
                                    || is_dir_name (info_parsed_filename)))
        {
          info_up_label_of_node (window->node);
          if (!info_parsed_nodename && (!info_parsed_filename
                                        || is_dir_name (info_parsed_filename)))
            {
              info_error ("%s",
                    _("No `Prev' or `Up' for this node within this document."));
              return 1;
            }
          else
            {
              info_handle_pointer ("Up", window);
            }
        }
      else
        {
          REFERENCE **menu;
          int inhibit_menu_traversing = 0;


          if (!info_parsed_filename && info_parsed_nodename)
            {
              char *pnode;

              pnode = xstrdup (info_parsed_nodename);
              info_up_label_of_node (window->node);

              if (!info_parsed_filename && info_parsed_nodename &&
                  strcmp (info_parsed_nodename, pnode) == 0)
                {


                  free (pnode);
                  inhibit_menu_traversing = 1;
                }
              else
                {
                  free (pnode);
                  info_prev_label_of_node (window->node);
                }
            }


          info_handle_pointer ("Prev", window);

          if (!inhibit_menu_traversing)
            {
              while (!info_error_was_printed &&
                     (menu = info_menu_of_node (window->node)))
                {
                  info_free_references (menu);
                  info_menu_digit (window, 1, '0');
                }
            }
        }
      break;
    }
  return 0;
}
