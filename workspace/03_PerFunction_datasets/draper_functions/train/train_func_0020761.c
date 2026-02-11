QCC_PR_Lex (void)
{
	int		c;

	pr_token[0] = 0;

	if (!pr_file_p)
	{
		if (QCC_PR_UnInclude())
		{
			QCC_PR_Lex();
			return;
		}
		pr_token_type = tt_eof;
		return;
	}

	QCC_PR_LexWhitespace ();

	if (!pr_file_p)
	{
		if (QCC_PR_UnInclude())
		{
			QCC_PR_Lex();
			return;
		}
		pr_token_type = tt_eof;
		return;
	}

	c = *pr_file_p;

	if (!c)
	{
		if (QCC_PR_UnInclude())
		{
			QCC_PR_Lex();
			return;
		}
		pr_token_type = tt_eof;
		return;
	}


	if (c == '\"')
	{
		QCC_PR_LexString ();
		return;
	}


	if (c == '\'')
	{
		QCC_PR_LexVector ();
		return;
	}


	if ( c == '~' || c == '%')
	{
		QCC_PR_ParseWarning(0, "~ or %% prefixes to denote integers are deprecated. Please use a postfix of 'i'");
		pr_file_p++;
		pr_token_type = tt_immediate;
		pr_immediate_type = type_integer;
		pr_immediate._int = QCC_PR_LexInteger ();
		return;
	}
	if ( c == '0' && pr_file_p[1] == 'x')
	{
		pr_token_type = tt_immediate;
		QCC_PR_LexNumber();
		return;
	}
	if ( (c == '.'&&pr_file_p[1] >='0' && pr_file_p[1] <= '9') || (c >= '0' && c <= '9') || ( c=='-' && pr_file_p[1]>='0' && pr_file_p[1] <='9') )
	{
		pr_token_type = tt_immediate;
		QCC_PR_LexNumber ();
		return;
	}

	if (c == '#' && !(pr_file_p[1]=='-' || (pr_file_p[1]>='0' && pr_file_p[1] <='9')))
	{
		pr_file_p++;
		if (!QCC_PR_CheakCompConst())
		{
			if (!QCC_PR_SimpleGetToken())
				strcpy(pr_token, "unknown");
			QCC_PR_ParseError(ERR_CONSTANTNOTDEFINED, "Explicit precompiler usage when not defined %s", pr_token);
		}
		else
			if (pr_token_type == tt_eof)
				QCC_PR_Lex();

		return;
	}

	if ( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_' )
	{
		if (flag_hashonly || !QCC_PR_CheakCompConst())
			QCC_PR_LexName ();
		else
			if (pr_token_type == tt_eof)
			{
				if (QCC_PR_UnInclude())
				{
					QCC_PR_Lex();
					return;
				}
				pr_token_type = tt_eof;
			}
		return;
	}

	if (c == '$')
	{
		QCC_PR_LexGrab ();
		return;
	}


	QCC_PR_LexPunctuation ();
}
