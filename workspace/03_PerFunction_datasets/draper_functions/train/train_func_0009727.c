select_expand(char *expand)
{
  if (state.cmd_line.macro_expand) {
    gpmessage(GPM_SUPLIN, NULL);
  } else {
    if (strcasecmp(expand, "ON") == 0) {
      state.lst.expand = true;
    } else if (strcasecmp(expand, "OFF") == 0) {
      state.lst.expand = false;
    } else {
      state.lst.expand = true;
      if (state.pass == 0) {
	fprintf(stderr,
		"Error: invalid option \"%s\"\n",
		expand);
      } else {
        gpwarning(GPE_ILLEGAL_ARGU, "Expected ON or OFF");
      }
    }
  }
}
