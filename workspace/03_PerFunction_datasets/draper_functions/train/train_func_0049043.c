doif(void)
{
   int                 flab1, flab2;
   int                 ifindent;

   ifindent = stmtindent;
   flab1 = getlabel();
   test(flab1, TRUE, FALSE);
   statement(NULL, FALSE);
   if (matchtoken(tELSE) == 0)
     {
	setlabel(flab1);
     }
   else
     {


#if 0
	if (stmtindent < ifindent && sc_tabsize > 0)
	   error(217);
#endif
	flab2 = getlabel();
	if ((lastst != tRETURN) && (lastst != tGOTO))
	   jumplabel(flab2);
	setlabel(flab1);
	statement(NULL, FALSE);
	setlabel(flab2);
     }
}
