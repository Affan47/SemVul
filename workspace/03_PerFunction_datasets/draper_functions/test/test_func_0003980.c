initialize_input_line (const char *prompt)
{
  input_line_prompt = prompt;
  if (prompt)
    strcpy (input_line, prompt);
  else
    input_line[0] = '\0';

  input_line_beg = input_line_end = input_line_point = strlen (prompt);
}
