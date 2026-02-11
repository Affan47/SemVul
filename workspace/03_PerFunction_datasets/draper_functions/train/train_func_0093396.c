is_pass_node(SGFNode *node, int boardsize)
{
  SGFProperty *sgf_prop;
  int i, j;


  if (!node->props)
    return 0;

  sgf_prop = node->props;
  while (sgf_prop) {
    switch (sgf_prop->name) {
    case SGFB:
    case SGFW:
      return !get_moveXY(sgf_prop, &i, &j, boardsize);
      break;
    default:
      break;
    }
    sgf_prop = sgf_prop->next;
  }

  return 0;
}
