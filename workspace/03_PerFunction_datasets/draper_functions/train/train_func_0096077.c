handleRankedElement(const ElementType *e)
{
  StringC rankSuffix(e->definition()->rankSuffix());
  const RankStem *rankStem = e->rankedElementRankStem();
  for (size_t i = 0; i < rankStem->nDefinitions(); i++) {
    const ElementDefinition *def = rankStem->definition(i);
    for (size_t j = 0; j < def->nRankStems(); j++)
      setCurrentRank(def->rankStem(j), rankSuffix);
  }
}
