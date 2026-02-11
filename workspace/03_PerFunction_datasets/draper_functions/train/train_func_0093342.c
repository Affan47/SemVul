compound(void)
{
   int                 indent = -1;
   cell                save_decl = declared;
   int                 count_stmt = 0;

   nestlevel += 1;
   while (matchtoken('}') == 0)
     {
	if (!freading)
	  {
	     needtoken('}');
	     break;
	  }
	else
	  {
	     if (count_stmt > 0
		 && (lastst == tRETURN || lastst == tBREAK
		     || lastst == tCONTINUE))
		error(225);
	     statement(&indent, TRUE);
	     count_stmt++;
	  }
     }
   if (lastst != tRETURN)
      destructsymbols(&loctab, nestlevel);
   if (lastst != tRETURN && lastst != tGOTO)

      modstk((int)(declared - save_decl) * sizeof(cell));

   testsymbols(&loctab, nestlevel, FALSE, TRUE);

   declared = save_decl;
   delete_symbols(&loctab, nestlevel, FALSE, TRUE);


   nestlevel -= 1;
}
