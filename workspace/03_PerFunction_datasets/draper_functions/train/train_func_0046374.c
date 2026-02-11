decl_const(int vclass)
{
   char                constname[sNAMEMAX + 1];
   cell                val;
   char               *str;
   int                 tag, exprtag;
   int                 symbolline;

   tag = sc_addtag(NULL);
   if (lex(&val, &str) != tSYMBOL)
      error(20, str);
   symbolline = fline;
   strcpy(constname, str);
   needtoken('=');
   constexpr(&val, &exprtag);
   needtoken(tTERM);

   if (!matchtag(tag, exprtag, FALSE))
     {


	int                 orgfline = fline;

	fline = symbolline;
	error(213);
	fline = orgfline;
     }
   add_constant(constname, val, vclass, tag);
}
