embDbiLogFile(AjPFile logfile, const AjPStr curfilename,
		   ajuint idCountFile, AjPStr const * fields,
		   const ajuint* countField,
		   ajuint nfields)
{
    ajuint i;

    ajFmtPrintF(logfile, "filename: '%S'\n", curfilename);
    ajFmtPrintF(logfile, "    id: %d\n", idCountFile);

    for(i=0;i<nfields;i++)
	ajFmtPrintF(logfile, "   %3S: %d\n", fields[i], countField[i]);

    return;
}
