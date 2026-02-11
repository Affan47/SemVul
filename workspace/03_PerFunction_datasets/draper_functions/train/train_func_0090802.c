PARSER_run(PARSECONTEXT *ctx, struct tagAST_BASE **rval  )
{
	int ret = 0;

#ifdef TRACE_PARSER
	yydebug = 1;
#endif

	ret = yyparse( ctx );
	if (ret) {

#ifdef TRACE_PARSER
	  fprintf( stderr, "---yyparer failed; returns %d\n", ret );
#endif
	  return ret;
	}

#ifdef TRACE_PARSER
	fprintf( stderr, "---yyparse ok\n" );
#endif


	*rval = ctx->my_ast_root;
	return ctx->my_yy_is_error;
}
