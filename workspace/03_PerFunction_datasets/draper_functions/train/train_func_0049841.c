info_parse_label (char *label, NODE *node)
{
  register int i;
  char *nodeline;


  save_nodename (NULL);
  save_filename (NULL);


  nodeline = node->contents;
  i = string_in_line (label, nodeline);

  if (i == -1)
    return;

  nodeline += i;
  nodeline += skip_whitespace (nodeline);
  info_parse_node (nodeline, PARSE_NODE_DFLT);
}
