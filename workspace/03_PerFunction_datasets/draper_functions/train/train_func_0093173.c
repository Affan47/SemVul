cross_reference (FILE_T f, NODE_T * p, LINE_T * l)
{
  if (p != NO_NODE && CROSS_REFERENCE_SAFE (&program)) {
    for (; p != NO_NODE; FORWARD (p)) {
      if (is_new_lexical_level (p) && l == LINE (INFO (p))) {
        TABLE_T *c = TABLE (SUB (p));
        ASSERT (snprintf (output_line, SNPRINTF_SIZE, "\n\n[level %d", LEVEL (c)) >= 0);
        WRITE (f, output_line);
        if (PREVIOUS (c) == a68g_standenv) {
          ASSERT (snprintf (output_line, SNPRINTF_SIZE, ", in standard environ") >= 0);
        } else {
          ASSERT (snprintf (output_line, SNPRINTF_SIZE, ", in level %d", LEVEL (PREVIOUS (c))) >= 0);
        }
        WRITE (f, output_line);
        ASSERT (snprintf (output_line, SNPRINTF_SIZE, ", %d increment]", AP_INCREMENT (c)) >= 0);
        WRITE (f, output_line);
        if (c != NO_TABLE) {
          xref_decs (f, c);
        }
        WRITE (f, "\n");
      }
      cross_reference (f, SUB (p), l);
    }
  }
}
