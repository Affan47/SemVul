clone( void ) const
{
	CommonASTWithHiddenTokens *ast = new CommonASTWithHiddenTokens( *this );
	return RefAST(ast);
}
