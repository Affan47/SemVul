ScanDocStart()
	{
		PopAllIndents();
		PopAllSimpleKeys();
		m_simpleKeyAllowed = false;


		Mark mark = INPUT.mark();
		INPUT.eat(3);
		m_tokens.push(Token(Token::DOC_START, mark));
	}
