yyparse()
{
     Ident identifier;

     level = 0;
     caller = NULL;
     clearstack();
     while (nexttoken()) {
	  identifier.storage = ExternStorage;
	  switch (tok.type) {
	  case 0:
	       return 0;
	  case QUALIFIER:
	       continue;
	  case TYPEDEF:
	       parse_typedef();
	       break;
	  case EXTERN:
	       identifier.storage = ExplicitExternStorage;
	       parse_declaration(&identifier, 0);
	       break;
	  case STATIC:
	       identifier.storage = StaticStorage;
	       nexttoken();

	  default:
	       parse_declaration(&identifier, 0);
	       break;
	  }
	  cleanup_stack();
     }
     return 0;
}
