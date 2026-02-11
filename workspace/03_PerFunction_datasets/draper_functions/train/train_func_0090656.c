perl_query(script_t *scr, script_query_t *scr_que, void *args[])
{
	int i;
	SV *perlargs[MAX_ARGS];
	SV *perlarg;

	int change = 1;

	PERL_HANDLER_HEADER((char *) scr_que->priv_data);
	for (i=0; i < scr_que->argc; i++) {

		perlarg = NULL;
		switch ( scr_que->argv_type[i] ) {
			case (QUERY_ARG_INT):
				perlarg = newSViv( *(int  *) args[i] );
				break;
			case (QUERY_ARG_CHARP):
				perlarg = new_pv(*(char **) args[i]);
				break;
			case (QUERY_ARG_CHARPP): {
				char *tmp = array_join((* (char ***) args[i]), " ");
				if (xstrlen(tmp))
					perlarg = new_pv(tmp);
				xfree(tmp);
				break;
				}
			case (QUERY_ARG_WINDOW):
				perlarg = ekg2_bless(BLESS_WINDOW, 0, (*(window_t **) args[i]));
				break;
			case (QUERY_ARG_FSTRING):
				perlarg = ekg2_bless(BLESS_FSTRING, 0, (*(fstring_t **) args[i]));
				break;
			default:
				debug("[NIMP] %s %d %d\n", __(query_name(scr_que->self->id)), i, scr_que->argv_type[i]);
		}

		if (!perlarg) perlarg = newSViv(0);
		if (change)   perlargs[i] = (perlarg = newRV_noinc(perlarg));
		XPUSHs(sv_2mortal(perlarg));
	}
#define PERL_RESTORE_ARGS 1
#include "perl_core.h"
	PERL_HANDLER_FOOTER();
#undef PERL_RESTORE_ARGS
}
