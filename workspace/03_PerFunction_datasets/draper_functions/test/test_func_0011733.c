ScanFlowStart()
	{

		InsertPotentialSimpleKey();
		m_simpleKeyAllowed = true;


		Mark mark = INPUT.mark();
		char ch = INPUT.get();
		FLOW_MARKER flowType = (ch == Keys::FlowSeqStart ? FLOW_SEQ : FLOW_MAP);
		m_flows.push(flowType);
		Token::TYPE type = (flowType == FLOW_SEQ ? Token::FLOW_SEQ_START : Token::FLOW_MAP_START);
		m_tokens.push(Token(type, mark));
	}
