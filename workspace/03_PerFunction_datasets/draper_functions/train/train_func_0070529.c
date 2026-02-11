parse(void)
{
   int                 tok, tag, fconst, fstock, fstatic;
   cell                val;
   char               *str;

   while (freading)
     {

	tok = lex(&val, &str);
	switch (tok)
	  {
	  case 0:

	     break;
	  case tNEW:
	     fconst = matchtoken(tCONST);
	     declglb(NULL, 0, FALSE, FALSE, FALSE, fconst);
	     break;
	  case tSTATIC:


	     fstock = matchtoken(tSTOCK);
	     fconst = matchtoken(tCONST);
	     tag = sc_addtag(NULL);
	     tok = lex(&val, &str);
	     if (tok == tNATIVE || tok == tPUBLIC)
	       {
		  error(42);
		  break;
	       }
	     declfuncvar(tok, str, tag, FALSE, TRUE, fstock, fconst);
	     break;
	  case tCONST:
	     decl_const(sGLOBAL);
	     break;
	  case tENUM:
	     decl_enum(sGLOBAL);
	     break;
	  case tPUBLIC:


	     fconst = matchtoken(tCONST);
	     tag = sc_addtag(NULL);
	     tok = lex(&val, &str);
	     if (tok == tNATIVE || tok == tSTOCK || tok == tSTATIC)
	       {
		  error(42);
		  break;
	       }
	     declfuncvar(tok, str, tag, TRUE, FALSE, FALSE, fconst);
	     break;
	  case tSTOCK:


	     fstatic = matchtoken(tSTATIC);
	     fconst = matchtoken(tCONST);
	     tag = sc_addtag(NULL);
	     tok = lex(&val, &str);
	     if (tok == tNATIVE || tok == tPUBLIC)
	       {
		  error(42);
		  break;
	       }
	     declfuncvar(tok, str, tag, FALSE, fstatic, TRUE, fconst);
	     break;
	  case tLABEL:
	  case tSYMBOL:
	  case tOPERATOR:
	     lexpush();
	     if (!newfunc(NULL, -1, FALSE, FALSE, FALSE))
	       {
		  error(10);
		  lexclr(TRUE);
	       }
	     break;
	  case tNATIVE:
	     funcstub(TRUE);
	     break;
	  case tFORWARD:
	     funcstub(FALSE);
	     break;
	  case '}':
	     error(54);
	     break;
	  case '{':
	     error(55);
	     break;
	  default:
	     if (freading)
	       {
		  error(10);
		  lexclr(TRUE);
	       }
	  }
     }
}
