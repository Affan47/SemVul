loop_report_error (LOOPSET *loop, int err,
			      const char *errline,
			      ExecState *state,
			      PRN *prn)
{
    int fd = gretl_function_depth();

    if (err) {
	if (fd == 0) {
	    errmsg(err, prn);
	    if (*errline != '\0') {
		pprintf(prn, ">> %s\n", errline);
	    }
	}
    } else if (loop->err) {
	if (fd == 0) {
	    errmsg(loop->err, prn);
	}
	err = loop->err;
    }

    if (fd > 0 && err && *errline != '\0') {
	strcpy(state->line, errline);
    }

    return err;
}
