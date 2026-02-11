find_footnotes_window (void)
{
  WINDOW *win;


  for (win = windows; win; win = win->next)
    if (internal_info_node_p (win->node) &&
        (strcmp (win->node->nodename, footnote_nodename) == 0))
      break;

  return win;
}
