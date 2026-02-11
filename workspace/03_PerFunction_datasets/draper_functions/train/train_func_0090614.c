parseTypeDeclarationStmt (tokenInfo *const token)
{
	Assert (isTypeSpec (token));
	parseTypeSpec (token);
	if (!isType (token, TOKEN_STATEMENT_END))
	{
		if (isType (token, TOKEN_COMMA))
			parseQualifierSpecList (token);
		if (isType (token, TOKEN_DOUBLE_COLON))
			readToken (token);
		parseEntityDeclList (token);
	}
	if (isType (token, TOKEN_STATEMENT_END))
		skipToNextStatement (token);
}
