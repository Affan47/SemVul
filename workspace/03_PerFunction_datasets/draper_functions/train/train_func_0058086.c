storeUniqueCmd(bool isTemp)
{
    fxStr emsg;
    u_int seqnum = getDocumentNumber(emsg);
    if (seqnum != (u_int) -1) {
	fxStr filename = fxStr::format("/%s/doc%u.%s"
	    , isTemp ? FAX_TMPDIR : FAX_DOCDIR
	    , seqnum
	    , formats[form].suffix
	);
	FILE* fout = fopen(filename, "w");
	if (fout != NULL) {
	    setFileOwner(filename);
	    FileCache::chmod(filename, 0640);
	    if (isTemp)
		tempFiles.append(filename);
	    time_t start_time = Sys::now();
	    int code;
	    FILE* din = openDataConn("r", code);
	    if (din != NULL) {
		reply(code, "FILE: %s (%s).", (const char*) filename,
		    dataConnMsg(code));
		file_size = -1;
		if (recvData(din, fout))
		    reply(226, "Transfer complete (FILE: %s).",
			(const char*) filename);
		if (TRACE(INXFERS) && xferfaxlog != -1)
		    logTransfer("i"
			, *dirLookup(isTemp ? "/" FAX_TMPDIR : "/" FAX_DOCDIR)
			, filename
			, start_time
		    );
		closeDataConn(din);
	    }
	    fclose(fout);
	} else
	    perror_reply(553, filename, errno);
    } else
	reply(553, "%s", (const char*)emsg);
}
