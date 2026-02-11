createTokenFromToken	(pANTLR3_BASE_TREE_ADAPTOR adaptor, pANTLR3_COMMON_TOKEN fromToken)
{
    pANTLR3_COMMON_TOKEN    newToken;

    newToken	= adaptor->tokenFactory->newToken(adaptor->tokenFactory);

    if	(newToken != NULL)
    {


		pANTLR3_STRING	text;

		newToken->toString  = fromToken->toString;

		if	(fromToken->textState == ANTLR3_TEXT_CHARP)
		{
			newToken->textState		= ANTLR3_TEXT_CHARP;
			newToken->tokText.chars	= fromToken->tokText.chars;
		}
		else
		{
			text						= fromToken->getText(fromToken);
			newToken->textState			= ANTLR3_TEXT_STRING;
			newToken->tokText.text	    = adaptor->strFactory->newPtr(adaptor->strFactory, text->chars, text->len);
		}

		newToken->setLine				(newToken, fromToken->getLine(fromToken));
		newToken->setTokenIndex			(newToken, fromToken->getTokenIndex(fromToken));
		newToken->setCharPositionInLine	(newToken, fromToken->getCharPositionInLine(fromToken));
		newToken->setChannel			(newToken, fromToken->getChannel(fromToken));
		newToken->setType				(newToken, fromToken->getType(fromToken));
    }

    return  newToken;
}
