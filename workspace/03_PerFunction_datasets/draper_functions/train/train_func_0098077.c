populate_defaults(struct ast_vm_user *vmu)
{
	ast_copy_flags(vmu, (&globalflags), AST_FLAGS_ALL);
	vmu->passwordlocation = passwordlocation;
	if (saydurationminfo) {
		vmu->saydurationm = saydurationminfo;
	}
	ast_copy_string(vmu->callback, callcontext, sizeof(vmu->callback));
	ast_copy_string(vmu->dialout, dialcontext, sizeof(vmu->dialout));
	ast_copy_string(vmu->exit, exitcontext, sizeof(vmu->exit));
	ast_copy_string(vmu->zonetag, zonetag, sizeof(vmu->zonetag));
	ast_copy_string(vmu->locale, locale, sizeof(vmu->locale));
	if (vmminsecs) {
		vmu->minsecs = vmminsecs;
	}
	if (vmmaxsecs) {
		vmu->maxsecs = vmmaxsecs;
	}
	if (maxmsg) {
		vmu->maxmsg = maxmsg;
	}
	if (maxdeletedmsg) {
		vmu->maxdeletedmsg = maxdeletedmsg;
	}
	vmu->volgain = volgain;
	ast_free(vmu->emailsubject);
	vmu->emailsubject = NULL;
	ast_free(vmu->emailbody);
	vmu->emailbody = NULL;
#ifdef IMAP_STORAGE
	ast_copy_string(vmu->imapfolder, imapfolder, sizeof(vmu->imapfolder));
	ast_copy_string(vmu->imapserver, imapserver, sizeof(vmu->imapserver));
	ast_copy_string(vmu->imapport, imapport, sizeof(vmu->imapport));
	ast_copy_string(vmu->imapflags, imapflags, sizeof(vmu->imapflags));
#endif
}
