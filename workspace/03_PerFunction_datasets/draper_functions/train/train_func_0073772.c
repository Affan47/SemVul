print_argv(interp,argc,argv)
Tcl_Interp *interp;
int argc;
char *argv[];
{
	static int buf_width_max = DEFAULT_WIDTH;
	static char buf_basic[DEFAULT_WIDTH+1];
	static char *buf = buf_basic;
	int space;
	int len;
	char *bufp;
	int proc;
	int arg_index;

	if (buf_width > buf_width_max) {
		if (buf && (buf != buf_basic)) ckfree(buf);
		buf = (char *)ckalloc(buf_width + 1);
		buf_width_max = buf_width;
	}

	proc = (0 == strcmp("proc",argv[0]));
	sprintf(buf,"%.*s",buf_width,argv[0]);
	len = strlen(buf);
	space = buf_width - len;
	bufp = buf + len;
	argc--; argv++;
	arg_index = 1;

	while (argc && (space > 0)) {
		CONST char *elementPtr;
		CONST char *nextPtr;
		int wrap;


		if (proc && (arg_index > 1)) wrap = TRUE;
		else {
			(void) TclFindElement(interp,*argv,
#if TCL_MAJOR_VERSION >= 8
					      -1,
#endif
				&elementPtr,&nextPtr,(int *)0,(int *)0);
			if (*elementPtr == '\0') wrap = TRUE;
			else if (*nextPtr == '\0') wrap = FALSE;
			else wrap = TRUE;
		}


		if (wrap) {
			sprintf(bufp," {%.*s}",space-3,*argv);
		} else {
			sprintf(bufp," %.*s",space-1,*argv);
		}
		len = strlen(buf);
		space = buf_width - len;
		bufp = buf + len;
		argc--; argv++;
		arg_index++;
	}

	if (compress) {


		strncpy(buf,printify(buf),buf_width);
	}


	if (strlen(buf) == buf_width) {
		buf[buf_width-1] = buf[buf_width-2] = buf[buf_width-3] = '.';
	}

	return(buf);
}
