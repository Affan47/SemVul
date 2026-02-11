DebugFsmTable(GrcManager * , std::ostream & strmOut, bool fWorking)
{
	int cfsmc = m_pfsm->NumberOfColumns();
	if (fWorking)
		strmOut << "\nWorking Table:          ";
	else
		strmOut << "\nFinal Table:            ";
	int ifsmc;
	for (ifsmc = 0; ifsmc < cfsmc; ifsmc++)
		OutputNumber(strmOut, ifsmc, 6);
	strmOut << "\n                          ";
	for (ifsmc = 0; ifsmc < cfsmc; ifsmc++)
		strmOut << "- - - ";


	size_t ifsLim = (fWorking)? m_pfsm->RawNumberOfStates() : m_vifsFinalToWork.size();
	for (size_t ifs = 0; ifs < ifsLim; ifs++)
	{
		FsmState * pfstate = (fWorking) ?
			m_pfsm->RawStateAt(ifs) :
			m_pfsm->StateAt(m_vifsFinalToWork[ifs]);

		strmOut << "\n" << ifs << ": " << pfstate->SlotsMatched() << "\n";

		if (pfstate->HasBeenMerged())
		{
			Assert(fWorking);
			strmOut << "  => state #" << pfstate->MergedState()->WorkIndex();
		}
		else
		{
			strmOut << "                        ";

			for (int ifsmc = 0; ifsmc < cfsmc; ifsmc++)
			{
				strmOut << " ";
				int ifsmcValue = pfstate->CellValue(ifsmc);
				if (!fWorking)
				{
					if (m_pfsm->RawStateAt(ifsmcValue)->HasBeenMerged())
						ifsmcValue = m_pfsm->RawStateAt(ifsmcValue)->MergedState()->WorkIndex();
					ifsmcValue = m_vifsWorkToFinal[ifsmcValue];
				}
				OutputNumber(strmOut, ifsmcValue, 5);
			}
		}

		pfstate->DebugFsmState(strmOut, ifs);
	}

	strmOut << "\n                          ";
	for (ifsmc = 0; ifsmc < cfsmc; ifsmc++)
		strmOut << "- - - ";
	strmOut << "\n\n";
}
