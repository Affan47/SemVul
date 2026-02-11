finish()
{
	if (!errflag &&
	    libmail_gpg_import_finish(&CursesAttachmentDisplay
				      ::KeyImportHelper::dump_func, this))
		errflag=true;

	return !errflag;
}
