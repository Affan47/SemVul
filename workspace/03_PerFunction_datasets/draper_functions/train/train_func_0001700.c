parse_file (const char *fname)
{
  yybegin (fname);
  for (;;)
    {
      switch (token ())
	{
	case EXTERN:
	case STATIC:
	  extern_or_static ();
	  break;

	case STRUCT:
	case UNION:
	  struct_or_union ();
	  break;

	case TYPEDEF:
	  typedef_decl ();
	  break;

	case DEFVEC_OP:
	case DEFVEC_I:
	  def_vec ();
	  break;

	case DEFVEC_ALLOC:
	  def_vec_alloc ();
	  break;

	case EOF_TOKEN:
	  goto eof;

	default:
	  parse_error ("unexpected top level token, %s", print_cur_token ());
	  goto eof;
	}
      lexer_toplevel_done = 1;
    }

 eof:
  advance ();
  yyend ();
}
