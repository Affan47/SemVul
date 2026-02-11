ParseFlow(Scanner *pScanner, const ParserState& state)
	{

		pScanner->pop();

		while(1) {
			if(pScanner->empty())
				throw ParserException(Mark::null(), ErrorMsg::END_OF_SEQ_FLOW);


			if(pScanner->peek().type == Token::FLOW_SEQ_END) {
				pScanner->pop();
				break;
			}


			Node *pNode = new Node;
			m_data.push_back(pNode);
			pNode->Parse(pScanner, state);


			Token& token = pScanner->peek();
			if(token.type == Token::FLOW_ENTRY)
				pScanner->pop();
			else if(token.type != Token::FLOW_SEQ_END)
				throw ParserException(token.mark, ErrorMsg::END_OF_SEQ_FLOW);
		}
	}
