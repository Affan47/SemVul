StartNewStyleCompile(void)
{
	if (setjmp(pr_parse_abort))
	{
		if (++pr_error_count > MAX_ERRORS)
			return;
		if (setjmp(pr_parse_abort))
			return;

		QCC_PR_SkipToSemicolon ();
		if (pr_token_type == tt_eof)
			return;
	}


	QCC_PR_ClearGrabMacros ();

	compilingfile = qccmprogsdat;

	pr_file_p = qccmsrc;
	s_file = s_file2 = QCC_CopyString (compilingfile);

	pr_source_line = 0;

	QCC_PR_NewLine (false);

	QCC_PR_Lex ();
}
