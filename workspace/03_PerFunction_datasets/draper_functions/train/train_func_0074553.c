getRoleExpression ( void )
{
	if ( Current != LBRACK )
		return getRole();

	NextLex();
	if ( scan.getExpressionKeyword() != L_INV )
		MustBe ( L_INV, "only role names and their inverses are allowed as a role expression" );
	NextLex();
	TORoleExpr* ret = EManager->Inverse(getORoleExpression());
	MustBeM(RBRACK);
	return ret;
}
