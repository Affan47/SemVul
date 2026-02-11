embDbiLogCmdline(AjPFile logfile)
{
    AjPStr cmdline = NULL;

    ajFmtPrintF(logfile, "########################################\n");
    ajFmtPrintF(logfile, "# Commandline: %S\n", ajUtilGetProgram());
    ajStrAssignS(&cmdline, ajUtilGetCmdline());

    if(ajStrGetLen(cmdline))
    {
	ajStrExchangeCC(&cmdline, "\n", "\1#    ");
	ajStrExchangeCC(&cmdline, "\1", "\n");
	ajFmtPrintF(logfile, "#    %S\n", cmdline);
    }

    ajStrAssignS(&cmdline, ajUtilGetInputs());

    if(ajStrGetLen(cmdline))
    {
	ajStrExchangeCC(&cmdline, "\n", "\1#    ");
	ajStrExchangeCC(&cmdline, "\1", "\n");
	ajFmtPrintF(logfile, "#    %S\n", cmdline);
    }

    ajFmtPrintF(logfile, "########################################\n\n");
    ajStrDel(&cmdline);

    return;
}
