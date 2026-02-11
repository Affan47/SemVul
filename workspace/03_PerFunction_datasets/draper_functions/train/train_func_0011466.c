Lex(TokenList *tokenList) {


   CND_PRECONDITION(tokenList != NULL, "tokens is NULL");


   while(true) {


	  QueryToken* token = _CLNEW QueryToken;
	  if ( !GetNextToken(token) ){
		_CLDELETE(token);
		break;
	  }
      tokenList->add(token);
   }


   tokenList->add(_CLNEW QueryToken( QueryToken::EOF_));
}
