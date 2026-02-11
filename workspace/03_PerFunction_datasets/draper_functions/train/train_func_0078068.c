PostAtomicWrite()
	{
		if(!good())
			return;

		EMITTER_STATE curState = m_pState->GetCurState();
		switch(curState) {

			case ES_WRITING_DOC:
				m_pState->SwitchState(ES_DONE_WITH_DOC);
				break;


			case ES_WRITING_BLOCK_SEQ_ENTRY:
				m_pState->SwitchState(ES_DONE_WITH_BLOCK_SEQ_ENTRY);
				break;


			case ES_WRITING_FLOW_SEQ_ENTRY:
				m_pState->SwitchState(ES_DONE_WITH_FLOW_SEQ_ENTRY);
				break;


			case ES_WRITING_BLOCK_MAP_KEY:
				m_pState->SwitchState(ES_DONE_WITH_BLOCK_MAP_KEY);
				break;
			case ES_WRITING_BLOCK_MAP_VALUE:
				m_pState->SwitchState(ES_DONE_WITH_BLOCK_MAP_VALUE);
				break;


			case ES_WRITING_FLOW_MAP_KEY:
				m_pState->SwitchState(ES_DONE_WITH_FLOW_MAP_KEY);
				break;
			case ES_WRITING_FLOW_MAP_VALUE:
				m_pState->SwitchState(ES_DONE_WITH_FLOW_MAP_VALUE);
				break;
			default:
				assert(false);
		};

		m_pState->ClearModifiedSettings();
	}
