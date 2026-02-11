DoExec(CONSFILE *pcf)
#else
DoExec(pcf)
    CONSFILE *pcf;
#endif
{
    showExecData = 1;
    FileWrite(cfstdout, FLAGFALSE, "exec: ", 6);

    GetUserInput(execCmd);
    FileWrite(cfstdout, FLAGFALSE, "]\r\n", 3);

    if (execCmd != (STRING *)0 && execCmd->used > 1) {
	ExecCmd();
	BuildString((char *)0, execCmd);
	if (execCmdFile == (CONSFILE *)0) {

	    FileSetQuoteIAC(pcf, FLAGFALSE);
	    FilePrint(pcf, FLAGFALSE, "%c%c", OB_IAC, OB_ABRT);
	    FileSetQuoteIAC(pcf, FLAGTRUE);
	} else {
	    char *r;

	    SetFlags(FileFDNum(pcf), 0, O_NONBLOCK);

	    FileSetQuoteIAC(pcf, FLAGFALSE);
	    FilePrint(pcf, FLAGFALSE, "%c%c", OB_IAC, OB_EXEC);
	    FileSetQuoteIAC(pcf, FLAGTRUE);
	    r = ReadReply(pcf, FLAGFALSE);

	    SetFlags(FileFDNum(pcf), O_NONBLOCK, 0);

	    if (strncmp(r, "[rw]", 4) != 0) {
		FileWrite(cfstdout, FLAGFALSE,
			  "[no longer read-write - aborting command]\r\n",
			  -1);
		FD_CLR(FileFDNum(execCmdFile), &rinit);
		FD_CLR(FileFDOutNum(execCmdFile), &winit);
		FileClose(&execCmdFile);
		FileSetQuoteIAC(pcf, FLAGFALSE);
		FilePrint(pcf, FLAGFALSE, "%c%c", OB_IAC, OB_ABRT);
		FileSetQuoteIAC(pcf, FLAGTRUE);
		kill(execCmdPid, SIGHUP);
	    }
	}
    } else {

	FileSetQuoteIAC(pcf, FLAGFALSE);
	FilePrint(pcf, FLAGFALSE, "%c%c", OB_IAC, OB_ABRT);
	FileSetQuoteIAC(pcf, FLAGTRUE);
    }
}
