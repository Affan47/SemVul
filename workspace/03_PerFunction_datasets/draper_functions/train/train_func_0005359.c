CreateRuleLookupManager(
  const InputType &sentence,
  const ChartCellCollectionBase &cellCollection)
{

  size_t maxChartSpan = 0;
  return new Scope3Parser(sentence, cellCollection, *this, maxChartSpan);
}
