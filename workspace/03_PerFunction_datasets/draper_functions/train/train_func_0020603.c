operator<<(std::ostream& out, const ChartHypothesis& hypo)
	{

		out << hypo.GetId();


		if (hypo.GetWinningHypothesis() != NULL &&
			hypo.GetWinningHypothesis() != &hypo)
		{
			out << "->" << hypo.GetWinningHypothesis()->GetId();
		}

		if (StaticData::Instance().GetIncludeLHSInSearchGraph()) {
			out << " " << hypo.GetTargetLHS() << "=>";
		}
		out << " " << hypo.GetCurrTargetPhrase()

			<< " " << hypo.GetCurrSourceRange();

		HypoList::const_iterator iter;
		for (iter = hypo.GetPrevHypos().begin(); iter != hypo.GetPrevHypos().end(); ++iter) {
			const ChartHypothesis &prevHypo = **iter;
			out << " " << prevHypo.GetId();
		}

		out << " [total=" << hypo.GetTotalScore() << "]";
		out << " " << hypo.GetScoreBreakdown();


		return out;
	}
