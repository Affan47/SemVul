main(int argc, char *argv[])
{
  LtLocale::tryToSetLocale();

 if(argc > 3)
  {
    usage(argv[0]);
  }

  switch(argc)
  {
    case 3:
      yyout = fopen(argv[2], "w");
      if(!yyout)
      {
        usage(argv[0]);
      }
    case 2:
      yyin = fopen(argv[1], "r");
      if(!yyin)
      {
        usage(argv[0]);
      }
      break;
    default:
      break;
  }

#ifdef WIN32
  _setmode(_fileno(yyin), _O_U8TEXT);
  _setmode(_fileno(yyout), _O_U8TEXT);
#endif

  yy_push_state(1);
  yy_top_state();
  yy_pop_state();

  S1_init();


  last = "";
  buffer = L"";
  isDot = hasWrite_dot = hasWrite_white = false;
  current=0;
  offset = 0;
  init_escape();
  init_tagNames();
  yylex();


  fclose(yyin);
  fclose(yyout);
}
