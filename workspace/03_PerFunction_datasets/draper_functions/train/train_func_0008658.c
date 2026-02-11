installed(mail::imap &imapAccount)
{
	const char *sep="%";

	if (oneFolderOnly)
		sep="";

	imapAccount.imapcmd("LIST", "LIST \"\" " +
		     imapAccount.quoteSimple(hier + sep) + "\r\n");
}
