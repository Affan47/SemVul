replace_definition_with_blank_lines(const char *start, const char *end, int skip)
{
  if ((include_directive_marker != NULL) && (C->out->f != NULL)) {
    while (start <= end) {
      if (*start == '\n') {
	if (skip) skip--; else fprintf(C->out->f,"\n");
      }
      start++;
    }
  }
}
