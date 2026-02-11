scoreFromSplice(unsigned i, unsigned j,
				   unsigned oldNumInplay,
				   unsigned& oldInplayPos) const {
  if (splicePrior <= 0.0) return LONG_MIN;
  long score = LONG_MIN;
  unsigned iSeq = rnameAndStrandIds[i];
  unsigned iEnd = cell(spliceEndCoords, i, j);

  for (; oldInplayPos < oldNumInplay; ++oldInplayPos) {
    unsigned k = oldInplayAlnIndices[oldInplayPos];
    if (rnameAndStrandIds[k] < iSeq) continue;
    if (rnameAndStrandIds[k] > iSeq) return score;
    if (rBegs[k] >= iEnd) return score;
    unsigned kBeg = cell(spliceBegCoords, k, j);
    if (kBeg >= rBegs[i] || rBegs[i] - kBeg <= maxSpliceDist) break;
  }

  int iScore = spliceEndScore(i, j);

  for (unsigned y = oldInplayPos; y < oldNumInplay; ++y) {
    unsigned k = oldInplayAlnIndices[y];
    if (rnameAndStrandIds[k] > iSeq) break;
    if (rBegs[k] >= iEnd) break;
    unsigned kBeg = cell(spliceBegCoords, k, j);
    if (iEnd <= kBeg) continue;
    if (iEnd - kBeg > maxSpliceDist) continue;
    int s = iScore + spliceBegScore(k, j) + spliceScore(iEnd - kBeg);
    score = std::max(score, cell(Vmat, k, j) + s);
  }

  return score;
}
