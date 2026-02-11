exp_exit_handlers(clientData)
ClientData clientData;
{
	extern int exp_forked;

	Tcl_Interp *interp = (Tcl_Interp *)clientData;


	static int did_app_exit = FALSE;
	static int did_expect_exit = FALSE;

	if (!did_expect_exit) {
		did_expect_exit = TRUE;

		if (exp_onexit_action) {
			int result = Tcl_GlobalEval(interp,exp_onexit_action);
			if (result != TCL_OK) Tcl_BackgroundError(interp);
		}
	} else {
		expDiagLogU("onexit handler called recursively - forcing exit\r\n");
	}

	if (exp_app_exit) {
		if (!did_app_exit) {
			did_app_exit = TRUE;
			(*exp_app_exit)(interp);
		} else {
			expDiagLogU("application exit handler called recursively - forcing exit\r\n");
		}
	}

	if (!exp_disconnected
	    && !exp_forked
	    && (exp_dev_tty != -1)
	    && isatty(exp_dev_tty)) {
	  if (exp_ioctled_devtty) {
		exp_tty_set(interp,&exp_tty_original,exp_dev_tty,0);
	  }
	}


	exp_close_all(interp);
}
