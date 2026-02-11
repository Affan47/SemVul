QCC_FinishCompile(void)
{
	pbool donesomething;
	int crc;

	currentchunk = NULL;

	if (setjmp(pr_parse_abort))
		QCC_Error(ERR_INTERNAL, "");

	if (!QCC_PR_FinishCompilation ())
	{
		QCC_Error (ERR_PARSEERRORS, "compilation errors");
	}


	if (pr_werror && pr_warning_count != 0)
		QCC_Error (ERR_PARSEERRORS, "compilation errors");


	crc = QCC_PR_WriteProgdefs ("progdefs.h");


	donesomething = QCC_WriteData (crc);


	QCC_BspModels ();


	QCC_CopyFiles ();

	if (donesomething)
	{
		printf ("Compile Complete\n\n");

		if (optres_shortenifnots)
			printf("optres_shortenifnots %i\n", optres_shortenifnots);
		if (optres_overlaptemps)
			printf("optres_overlaptemps %i\n", optres_overlaptemps);
		if (optres_noduplicatestrings)
			printf("optres_noduplicatestrings %i\n", optres_noduplicatestrings);
		if (optres_constantarithmatic)
			printf("optres_constantarithmatic %i\n", optres_constantarithmatic);
		if (optres_nonvec_parms)
			printf("optres_nonvec_parms %i\n", optres_nonvec_parms);
		if (optres_constant_names)
			printf("optres_constant_names %i\n", optres_constant_names);
		if (optres_constant_names_strings)
			printf("optres_constant_names_strings %i\n", optres_constant_names_strings);
		if (optres_precache_file)
			printf("optres_precache_file %i\n", optres_precache_file);
		if (optres_filenames)
			printf("optres_filenames %i\n", optres_filenames);
		if (optres_assignments)
			printf("optres_assignments %i\n", optres_assignments);
		if (optres_unreferenced)
			printf("optres_unreferenced %i\n", optres_unreferenced);
		if (optres_locals)
			printf("optres_locals %i\n", optres_locals);
		if (optres_function_names)
			printf("optres_function_names %i\n", optres_function_names);
		if (optres_dupconstdefs)
			printf("optres_dupconstdefs %i\n", optres_dupconstdefs);
		if (optres_return_only)
			printf("optres_return_only %i\n", optres_return_only);
		if (optres_compound_jumps)
			printf("optres_compound_jumps %i\n", optres_compound_jumps);


		if (optres_stripfunctions)
			printf("optres_stripfunctions %i\n", optres_stripfunctions);
		if (optres_locals_marshalling)
			printf("optres_locals_marshalling %i\n", optres_locals_marshalling);
		if (optres_logicops)
			printf("optres_logicops %i\n", optres_logicops);


		if (optres_test1)
			printf("optres_test1 %i\n", optres_test1);
		if (optres_test2)
			printf("optres_test2 %i\n", optres_test2);

		printf("numtemps %i\n", numtemps);

		printf("%i warnings\n", pr_warning_count);
	}

	qcc_compileactive = false;
}
