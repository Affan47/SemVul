dirdcl(Ident *idptr)
{
     int wrapper = 0;
     int *parm_ptr = NULL;

     if (tok.type == '(') {
	  dcl(idptr);
	  if (tok.type != ')' && verbose) {
	       file_error(_("expected `)'"), &tok);
	       return 1;
	  }
     } else if (tok.type == IDENTIFIER) {
	  if (idptr) {
	       idptr->name = tok.token;
	       idptr->line = tok.line;
	       parm_ptr = &idptr->parmcnt;
	  }
     }

     if (nexttoken() == PARM_WRAPPER) {
	  wrapper = 1;
	  nexttoken();
     } else
	  putback();

     while (nexttoken() == '[' || tok.type == '(') {
	  if (tok.type == '[')
	       skip_to(']');
	  else {
	       maybe_parm_list(parm_ptr);
	       if (tok.type != ')' && verbose) {
		    file_error(_("expected `)'"), &tok);
		    return 1;
	       }
	  }
     }
     if (wrapper)
	  nexttoken();

     while (tok.type == PARM_WRAPPER) {
	  if (skip_balanced('(', ')', 0) == -1)
	       file_error(_("unexpected end of file in function declaration"),
			  NULL);
     }

     return 0;
}
