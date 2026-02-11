mxmlSaveFile(mxml_node_t *node,
             FILE        *fp,
	     const char  *(*cb)(mxml_node_t *node, int ws))

{
  int	col;


  if ((col = mxml_write_node(node, fp, cb, 0, mxml_file_putc)) < 0)
    return (-1);

  if (col > 0)
    if (putc('\n', fp) < 0)
      return (-1);


  return (0);
}
