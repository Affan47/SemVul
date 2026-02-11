main(int argc, char *argv[])
{
  char modedir[STR_LEN] = "i2g/";

  if (parse_parameters(argc, argv, (char *)modedir))
    return 1;

  if (load_syntax_files(modedir))
    return 2;

  retrieve_comment_styles();


  if (flags & FLAG_INLINEMODE) {
    if (modedir[0] == 'g')
      printHelp("Error: gas -> Intel conversion not supported for inline asm\n");
    addComment("//","//");
  }

  if (comments == 0) {
    fprintf(stderr, "Error: No comments defined\n");
    return 3;
  }

  return main_parse_loop();
}
