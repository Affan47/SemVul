NumSuccessStates()
{
	int cRet = 0;
	size_t ifsLim = m_vifsFinalToWork.size();
	for (size_t ifs = 0; ifs < ifsLim; ifs++)
	{
		FsmState * pfstate = m_pfsm->StateAt(m_vifsFinalToWork[ifs]);

		Assert(!pfstate->HasBeenMerged());

		if (pfstate->NumberOfRulesSucceeded() > 0)
			cRet++;
	}
	return cRet;
}
