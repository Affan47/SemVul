StatesMatch(FsmState * pfstate)
{
	Assert(m_critSlotsMatched == pfstate->m_critSlotsMatched);

	if (NumberOfRulesMatched() != pfstate->NumberOfRulesMatched())
		return false;
	if (NumberOfRulesSucceeded() != pfstate->NumberOfRulesSucceeded())
		return false;

	std::set<int>::iterator it;
	for (it = m_setiruleMatched.begin();
		it != m_setiruleMatched.end();
		++it)
	{
		if (!pfstate->RuleMatched(*it))
			return false;
	}

	for (it = m_setiruleSuccess.begin();
		it != m_setiruleSuccess.end();
		++it)
	{
		if (!pfstate->RuleSucceeded(*it))
			return false;
	}

	return true;
}
