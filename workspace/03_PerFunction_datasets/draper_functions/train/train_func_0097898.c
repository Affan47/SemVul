fprint_parse_error(FILE *fp, char *msg, String_buf sb,
			int start_pos, int end_pos)
{
  int i;
  int n = sb_size(sb);
  if (end_pos == -1)
    end_pos = n-1;
  fprintf(fp, "%%%%ERROR: %s:\n\n", msg);
  for (i = 0; i < start_pos; i++)
    fprintf(fp, "%c", sb_char(sb, i));
  fprintf(fp, "%%%%START ERROR%%%%");
  for (i = start_pos; i <= end_pos; i++)
    fprintf(fp, "%c", sb_char(sb, i));
  fprintf(fp, "%%%%END ERROR%%%%");
  for (i = end_pos+1; i < n; i++)
    fprintf(fp, "%c", sb_char(sb, i));
  fprintf(fp, "\n");
}
