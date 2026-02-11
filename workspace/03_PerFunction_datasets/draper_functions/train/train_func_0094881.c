main(int argc, char *argv[])
{
  int i, status = 200;


  set_error_handler(handle_error);
  set_start_handler(start);
  set_end_handler(end);
  set_comment_handler(handle_comment);
  set_text_handler(handle_text);
  set_decl_handler(handle_decl);
  set_pi_handler(handle_pi);
  set_starttag_handler(handle_starttag);
  set_emptytag_handler(handle_emptytag);
  set_endtag_handler(handle_endtag);


  for (i = 1; i < argc && argv[i][0] == '-' && !eq(argv[i], "--"); i++) {
    switch (argv[i][1]) {
      case 'd': do_decls = false; break;
      default: usage(argv[0]);
    }
  }
  if (i < argc && eq(argv[i], "--")) i++;

  if (i == argc) yyin = stdin;
  else if (i == argc - 1) yyin = fopenurl(argv[i], "r", &status);
  else usage(argv[0]);

  if (yyin == NULL) {perror(argv[i]); exit(1);}
  if (status != 200) errexit("%s : %s\n", argv[i], http_strerror(status));

  if (yyparse() != 0) exit(3);

  return has_error ? 1 : 0;
}
