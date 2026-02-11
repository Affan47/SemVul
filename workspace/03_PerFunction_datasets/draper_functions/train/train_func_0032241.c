GenerateRuleMaps(std::vector<int> & vnOffsets, std::vector<int> & vnRuleList)
{
	size_t ifsLim = m_vifsFinalToWork.size();
	for (size_t ifs = 0; ifs < ifsLim; ifs++)
	{
		FsmState * pfstate = m_pfsm->StateAt(m_vifsFinalToWork[ifs]);

		Assert(!pfstate->HasBeenMerged());

		if (pfstate->NumberOfRulesSucceeded() > 0)
		{
			vnOffsets.push_back(vnRuleList.size());


			std::vector<int> virule;
			for (std::set<int>::iterator itset = pfstate->m_setiruleSuccess.begin();
				itset != pfstate->m_setiruleSuccess.end();
				++itset)
			{
				for (size_t iirule = 0; iirule <= virule.size(); iirule++)
				{
					if (iirule == virule.size())
					{
						virule.push_back(*itset);
						break;
					}
					else if (*itset < virule[iirule])
					{
						virule.insert(virule.begin() + iirule, *itset);
						break;
					}
				}
			}

			for (size_t iirule = 0; iirule < virule.size(); iirule++)
				vnRuleList.push_back(virule[iirule]);
		}
		else
		{

			Assert(vnRuleList.size() == 0);
		}
	}


	vnOffsets.push_back(vnRuleList.size());
}
