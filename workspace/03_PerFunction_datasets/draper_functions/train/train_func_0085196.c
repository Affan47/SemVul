ftpListingFinish(FtpStateData * ftpState)
{
    StoreEntry *e = ftpState->entry;
    storeAppendPrintf(e, "</PRE>\n");
    if (ftpState->flags.listformat_unknown && !ftpState->flags.tried_nlst) {
	storeAppendPrintf(e, "<A HREF=\"%s/;type=d\">[As plain directory]</A>\n",
	    ftpState->flags.dir_slash ? rfc1738_escape_part(ftpState->old_filepath) : ".");
    } else if (ftpState->typecode == 'D') {
	const char *path = ftpState->flags.dir_slash ? ftpState->filepath : ".";
	storeAppendPrintf(e, "<A HREF=\"%s/\">[As extended directory]</A>\n", rfc1738_escape_part(path));
    }
    storeAppendPrintf(e, "<HR noshade size=\"1px\">\n");
    storeAppendPrintf(e, "<ADDRESS>\n");
    storeAppendPrintf(e, "Generated %s by %s (%s)\n",
	mkrfc1123(squid_curtime),
	getMyHostname(),
	visible_appname_string);
    storeAppendPrintf(e, "</ADDRESS></BODY></HTML>\n");
}
