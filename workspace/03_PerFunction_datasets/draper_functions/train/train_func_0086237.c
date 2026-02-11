list_source_line (FILE_T f, LINE_T * line, BOOL_T tree)
{
  int k = (int) strlen (STRING (line)) - 1;
  if (NUMBER (line) <= 0) {

    return;
  }
  if ((STRING (line))[k] == NEWLINE_CHAR) {
    (STRING (line))[k] = NULL_CHAR;
  }

  write_source_line (f, line, NO_NODE, A68_ALL_DIAGNOSTICS);

  if (OPTION_CROSS_REFERENCE (&program)) {
    cross_reference (f, TOP_NODE (&program), line);
  }

  if (tree && OPTION_TREE_LISTING (&program)) {
    if (TREE_LISTING_SAFE (&program) && leaves_to_print (TOP_NODE (&program), line)) {
      int ld = -1, k2;
      WRITE (f, "\n\nSyntax tree");
      for (k2 = 0; k2 < BUFFER_SIZE; k2++) {
        bar[k2] = " ";
      }
      tree_listing (f, TOP_NODE (&program), 1, line, &ld);
      WRITE (f, "\n");
    }
  }
}
