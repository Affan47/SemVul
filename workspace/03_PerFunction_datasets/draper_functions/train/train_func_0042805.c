create()
{
	ASTNode* node = nodeFactory();
	node->setType(Token::INVALID_TYPE);
	return RefAST(new AST(node));
}
