write_tree_listing (void)
{
  LINE_T *line = TOP_LINE (&program);
  FILE_T f = FILE_LISTING_FD (&program);
  int listed = 0;
  WRITE (FILE_LISTING_FD (&program), NEWLINE_STRING);
  WRITE (FILE_LISTING_FD (&program), "\nSyntax tree listing");
  WRITE (FILE_LISTING_FD (&program), "\n------ ---- -------");
  WRITE (FILE_LISTING_FD (&program), NEWLINE_STRING);
  if (FILE_LISTING_OPENED (&program) == 0) {
    diagnostic_node (A68_ERROR, NO_NODE, ERROR_CANNOT_WRITE_LISTING);
    return;
  }
  for (; line != NO_LINE; FORWARD (line)) {
    if (NUMBER (line) > 0 && LIST (line)) {
      listed++;
    }
    list_source_line (f, line, A68_TRUE);
  }

  if (listed == 0) {
    ASSERT (snprintf (output_line, SNPRINTF_SIZE, "\n     No lines to list") >= 0);
    WRITE (f, output_line);
  }
}
