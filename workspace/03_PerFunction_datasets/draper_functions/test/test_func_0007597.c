calcDiff(calc_ *r, char *variable, double *solution)
{
	tokenSolveArgs_ args;

	ReturnErrIf(r == NULL);
	ReturnErrIf(solution == NULL);
	ReturnErrIf(variable == NULL);

	args.parser = r->parser;
	args.solution = solution;

	ReturnErrIf(hashFind(r->variables, variable, (void*)&args.diffVariable));
	ReturnErrIf(args.diffVariable == NULL,
			"Couldn't find variable %s.", variable);


	Debug("%s", ParseTokenName(TOKEN_DIFF));
	Parse(r->parser, TOKEN_DIFF, NULL, solution);
	ReturnErrIf(isnan(*solution), "Parser failed");

	ReturnErrIf(listExecute(r->tokens, (listExecute_)tokenSolve, &args));
	ReturnErrIf(isnan(*solution), "Parser failed");

	return 0;
}
