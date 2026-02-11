print_to_asm_out_file (print_switch_type type, const char * text)
{
  bool prepend_sep = true;

  switch (type)
    {
    case SWITCH_TYPE_LINE_END:
      putc ('\n', asm_out_file);
      return 1;

    case SWITCH_TYPE_LINE_START:
      fputs (ASM_COMMENT_START, asm_out_file);
      return strlen (ASM_COMMENT_START);

    case SWITCH_TYPE_DESCRIPTIVE:
      if (ASM_COMMENT_START[0] == 0)
	prepend_sep = false;

    case SWITCH_TYPE_PASSED:
    case SWITCH_TYPE_ENABLED:
      if (prepend_sep)
	fputc (' ', asm_out_file);
      fputs (text, asm_out_file);


      return 0;

    default:
      return -1;
    }
}
