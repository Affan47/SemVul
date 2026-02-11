init_branch()
{
	if(++n_brs > BRANCH_LIMIT) {

		yyerror("FATAL - Too many special levels defined.");
		exit(EXIT_FAILURE);
	}
	tmpbranch[n_brs].lev.base = 0;
	tmpbranch[n_brs].lev.rand = 0;
	Strcpy(tmpbranch[n_brs].name, "");
	tmpbranch[n_brs].chain = -1;
}
