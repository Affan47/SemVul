hypstates(long chars, node *root, pointarray treenode, gbases **garbage)
{


  long i, n;
  discbaseptr nothing;

  fprintf(outfile, "\nFrom    To     Any Steps?    State at upper node\n");
  fprintf(outfile, "                            ");
  if (dotdiff)
    fprintf(outfile, " ( . means same as in the node below it on tree)\n");
  nothing = (discbaseptr)Malloc(endsite*sizeof(unsigned char));
  for (i = 0; i < endsite; i++)
    nothing[i] = 0;
  for (i = 1; i <= ((chars - 1) / 40 + 1); i++) {
    putc('\n', outfile);
    n = i * 40;
    if (n > chars)
      n = chars;
    hyptrav(root, nothing, i * 40 - 39, n, true, treenode, garbage);
  }
  free(nothing);
}
