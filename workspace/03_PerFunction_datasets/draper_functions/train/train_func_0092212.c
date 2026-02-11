next_input_file(void)
{
#define rsm          (G.next_input_file__rsm)
#define files_happen (G.next_input_file__files_happen)

	FILE *F = NULL;
	const char *fname, *ind;

	if (rsm.F)
		fclose(rsm.F);
	rsm.F = NULL;
	rsm.pos = rsm.adv = 0;

	do {
		if (getvar_i(intvar[ARGIND])+1 >= getvar_i(intvar[ARGC])) {
			if (files_happen)
				return NULL;
			fname = "-";
			F = stdin;
		} else {
			ind = getvar_s(incvar(intvar[ARGIND]));
			fname = getvar_s(findvar(iamarray(intvar[ARGV]), ind));
			if (fname && *fname && !is_assignment(fname))
				F = xfopen_stdin(fname);
		}
	} while (!F);

	files_happen = TRUE;
	setvar_s(intvar[FILENAME], fname);
	rsm.F = F;
	return &rsm;
#undef rsm
#undef files_happen
}
