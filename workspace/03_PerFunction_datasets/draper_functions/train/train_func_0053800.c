write_stream(char *name)
#else
FILE *write_stream(name)
char *name;
#endif
{
	FILE *f;

	if (name){
		if (name[0] == '-') {
			fprintf(stderr, "dlg: invalid option: '%s'\n", name);
			f = NULL;
		}else{
			f = fopen(OutMetaName(name), "w");
			if (f == NULL){

				fprintf(stderr,
					"dlg: Warning: Can't write to file %s.\n",
					name);
			}
			else
#ifdef SPECIAL_FOPEN
                special_fopen_actions(OutMetaName(name));
#else
		;
#endif
		}
	}else{

		f = stdout;
	}
	return f;
}
