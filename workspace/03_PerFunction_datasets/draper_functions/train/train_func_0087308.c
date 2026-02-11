s_1paus(FILE *fin)
#endif
{
	fprintf(stderr,
	"To resume execution, type go.  Other input will terminate the job.\n");
	fflush(stderr);
	if( getc(fin)!='g' || getc(fin)!='o' || getc(fin)!='\n' ) {
		fprintf(stderr, "STOP\n");
#ifdef NO_ONEXIT
		f_exit();
#endif
		exit(0);
		}
	}
