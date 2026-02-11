genexmsgmulti(BW *bw, int saved, int skipped)
{
	if (saved)
		if (skipped)
			joe_snprintf_0(msgbuf, JOE_MSGBUFSIZE, joe_gettext(_("Some files have not been saved.")));
		else
			joe_snprintf_0(msgbuf, JOE_MSGBUFSIZE, joe_gettext(_("All modified files have been saved.")));
	else
		joe_snprintf_0(msgbuf, JOE_MSGBUFSIZE, joe_gettext(_("No modified files, so no updates needed.")));

	msgnw(bw->parent, msgbuf);

	exmsg = vsncpy(NULL,0,sz(msgbuf));
}
