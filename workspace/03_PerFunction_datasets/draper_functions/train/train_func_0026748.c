yyinit(int argc, char **argv)
{
	Binit(&bstdout, 1, OWRITE);
	sargv = argv;
	sargc = argc;
	if(sargc == 0) {
		in = &bstdin;
		Binit(in, 0, OREAD);
	} else if((in = Bopen(sargv[0], OREAD)) == 0)
		yyerror("cannot open input file");
	ifile = 0;
	ln = 0;
	ss = sargv[0];
}
