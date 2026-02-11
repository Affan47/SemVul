compareRules(void)
{


	unsigned int old = 0;
	unsigned int new = 0;

	int compare = 0;

	while (new < newargc && old < oldargc) {
		if (isTarget(oldargv[old]) && isTarget(newargv[new])) {


			if (((strcmp((oldargv[old]), "-j") == 0
					|| strcmp((oldargv[old]), "--jump") == 0)
				&& old+1 < oldargc
				&& isTerminatingTarget(oldargv[old+1]) )
			    || strcmp((oldargv[old]), "-g") == 0
			    || strcmp((oldargv[old]), "--goto") == 0 ) {

				compare = 0;
			} else {
				compare = 1;
			}
			break;
		}

		if (strcmp(oldargv[old], newargv[new]) != 0) {
			compare = 0;
			break;
		}

		old++;
		new++;
	}


	return compare == 1;
}
