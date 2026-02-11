Job_CheckCommands(GNode *gn, void (*abortProc)(const char *, ...))
{

	if (OP_NOP(gn->type) && Lst_IsEmpty(&gn->commands) &&
	    (gn->type & OP_LIB) == 0) {


		if (DEFAULT != NULL && !Lst_IsEmpty(&DEFAULT->commands)) {


			Make_HandleUse(DEFAULT, gn);
			Var_Set(IMPSRC, Var_Value(TARGET, gn), gn);

		} else if (Dir_MTime(gn) == 0) {


			static const char msg[] =
			    "make: don't know how to make";

			if (gn->type & OP_OPTIONAL) {
				fprintf(stdout, "%s %s(ignored)\n",
				    msg, gn->name);
				fflush(stdout);
			} else if (keepgoing) {
				fprintf(stdout, "%s %s(continuing)\n",
				    msg, gn->name);
				fflush(stdout);
				return (FALSE);
			} else {
#ifndef WITHOUT_OLD_JOKE
				if (strcmp(gn->name,"love") == 0)
					(*abortProc)("Not war.");
				else
#endif
					(*abortProc)("%s %s. Stop",
					    msg, gn->name);
				return (FALSE);
			}
		}
	}
	return (TRUE);
}
