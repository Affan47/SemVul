equals (char *sym_name, int reassign)
{
  char *stop = NULL;
  char stopc = 0;

  input_line_pointer++;
  if (*input_line_pointer == '=')
    input_line_pointer++;
  if (reassign < 0 && *input_line_pointer == '=')
    input_line_pointer++;

  while (*input_line_pointer == ' ' || *input_line_pointer == '\t')
    input_line_pointer++;

  if (flag_mri)
    stop = mri_comment_field (&stopc);

  assign_symbol (sym_name, reassign >= 0 ? !reassign : reassign);

  if (flag_mri)
    {
      demand_empty_rest_of_line ();
      mri_comment_end (stop, stopc);
    }
}
