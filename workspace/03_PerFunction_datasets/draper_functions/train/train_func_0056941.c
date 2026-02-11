handle_eval_error(interp,check_for_nostack)
Tcl_Interp *interp;
int check_for_nostack;
{
	char *msg;


	msg = Tcl_GetVar(interp,"errorInfo",TCL_GLOBAL_ONLY);
    if (!msg) msg = Tcl_GetStringResult (interp);
	else if (check_for_nostack) {


		if (0 == strncmp("-nostack",msg,8)) return;


		if (exp_nostack_dump) {
			exp_nostack_dump = FALSE;
			return;
		}
	}


	expErrorLogU(exp_cook(msg,(int *)0));
	expErrorLogU("\r\n");
}
