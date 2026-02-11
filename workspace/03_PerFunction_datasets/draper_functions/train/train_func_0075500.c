CleanupArcList()
	{

		m_winningHypo = this;

		if (!m_arcList) return;


		const StaticData &staticData = StaticData::Instance();
		size_t nBestSize = staticData.GetNBestSize();
		bool distinctNBest = staticData.GetDistinctNBest() || staticData.UseMBR() || staticData.GetOutputSearchGraph();

		if (!distinctNBest && m_arcList->size() > nBestSize) {

			nth_element(m_arcList->begin()
				, m_arcList->begin() + nBestSize - 1
				, m_arcList->end()
				, CompareChartChartHypothesisTotalScore());


			ChartArcList::iterator iter;
			for (iter = m_arcList->begin() + nBestSize ; iter != m_arcList->end() ; ++iter) {
				ChartHypothesis *arc = *iter;
				ChartHypothesis::Delete(arc);
			}
			m_arcList->erase(m_arcList->begin() + nBestSize
				, m_arcList->end());
		}


		ChartArcList::iterator iter = m_arcList->begin();
		for (; iter != m_arcList->end() ; ++iter) {
			ChartHypothesis *arc = *iter;
			arc->SetWinningHypo(this);
		}


	}
