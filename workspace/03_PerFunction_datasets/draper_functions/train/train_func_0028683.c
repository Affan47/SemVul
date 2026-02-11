SetBoolFormat(EMITTER_MANIP value)
	{
		bool ok = false;
		if(m_pState->SetBoolFormat(value, GLOBAL))
			ok = true;
		if(m_pState->SetBoolCaseFormat(value, GLOBAL))
			ok = true;
		if(m_pState->SetBoolLengthFormat(value, GLOBAL))
			ok = true;
		return ok;
	}
