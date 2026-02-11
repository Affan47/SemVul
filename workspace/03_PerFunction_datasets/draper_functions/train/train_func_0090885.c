skip_struct()
{
     if (nexttoken() == IDENTIFIER) {
	  nexttoken();
     } else if (tok.type == ';')
	  return;

     if (tok.type == LBRACE || tok.type == LBRACE0) {
	  if (skip_balanced('{', '}', 1) == -1) {
	       file_error(_("unexpected end of file in struct"), NULL);
	       return;
	  }
     }

     while (tok.type == PARM_WRAPPER) {
	  if (skip_balanced('(', ')', 0) == -1)
	      file_error(_("unexpected end of file in struct"), NULL);
     }
}
