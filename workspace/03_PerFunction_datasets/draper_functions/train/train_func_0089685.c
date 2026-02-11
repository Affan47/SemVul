CreateDeviantPaths(TrellisPathList &pathColl) const
{
  const size_t sizePath = m_path.size();

  if (m_prevEdgeChanged == NOT_FOUND) {

    for (size_t currEdge = 0 ; currEdge < sizePath ; currEdge++) {
      const Hypothesis	*hypo		= static_cast<const Hypothesis*>(m_path[currEdge]);
      const ArcList *pAL = hypo->GetArcList();
      if (!pAL) continue;
      const ArcList &arcList = *pAL;


      ArcList::const_iterator iterArc;
      for (iterArc = arcList.begin() ; iterArc != arcList.end() ; ++iterArc) {
        const Hypothesis *arc = *iterArc;
        TrellisPath *deviantPath = new TrellisPath(*this, currEdge, arc);
        pathColl.Add(deviantPath);
      }
    }
  } else {

    for (size_t currEdge = m_prevEdgeChanged + 1 ; currEdge < sizePath ; currEdge++) {
      const ArcList *pAL = m_path[currEdge]->GetArcList();
      if (!pAL) continue;
      const ArcList &arcList = *pAL;
      ArcList::const_iterator iterArc;

      for (iterArc = arcList.begin() ; iterArc != arcList.end() ; ++iterArc) {

        const Hypothesis *arcReplace = *iterArc;

        TrellisPath *deviantPath = new TrellisPath(*this, currEdge, arcReplace);
        pathColl.Add(deviantPath);
      }
    }
  }
}
