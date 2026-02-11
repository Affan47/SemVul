ScanFlowEntry()
	{

		if(VerifySimpleKey())
			m_tokens.push(Token(Token::VALUE, INPUT.mark()));

		m_simpleKeyAllowed = true;


		Mark mark = INPUT.mark();
		INPUT.eat(1);
		m_tokens.push(Token(Token::FLOW_ENTRY, mark));
	}
