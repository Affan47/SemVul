yywrap()
{
     if (!yyin)
	  return 1;
     if (preprocess_option)
	  pp_close(yyin);
     else
	  fclose(yyin);
     yyin = NULL;
#ifdef FLEX_SCANNER
     yy_delete_buffer(YY_CURRENT_BUFFER);
#endif
     delete_statics();
     return 1;
}
