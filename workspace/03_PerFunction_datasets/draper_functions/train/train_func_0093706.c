save_srch(FILE *f)
{
	if(globalsrch) {
		if(globalsrch->pattern) {
			fprintf(f,"	pattern ");
			emit_string(f,globalsrch->pattern,sLEN(globalsrch->pattern));
			fprintf(f,"\n");
		}
		if(globalsrch->replacement) {
			fprintf(f,"	replacement ");
			emit_string(f,globalsrch->replacement,sLEN(globalsrch->replacement));
			fprintf(f,"\n");
		}
		fprintf(f,"	backwards %d\n",globalsrch->backwards);
		fprintf(f,"	ignore %d\n",globalsrch->ignore);
		fprintf(f,"	replace %d\n",globalsrch->replace);
		fprintf(f,"	block_restrict %d\n",globalsrch->block_restrict);
	}
	fprintf(f,"done\n");
}
