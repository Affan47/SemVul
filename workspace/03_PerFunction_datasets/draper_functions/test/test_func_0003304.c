GetChartRuleCollection(
  const WordsRange &range,
  ChartParserCallback &outColl)
{
  size_t relEndPos = range.GetEndPos() - range.GetStartPos();
  size_t absEndPos = range.GetEndPos();


  DottedRuleColl &dottedRuleCol = *m_dottedRuleColls[range.GetStartPos()];
  const DottedRuleList &expandableDottedRuleList = dottedRuleCol.GetExpandableDottedRuleList();


  for (size_t ind = 0; ind < expandableDottedRuleList.size(); ++ind) {

    const DottedRuleInMemory &prevDottedRule = *expandableDottedRuleList[ind];

    size_t startPos = prevDottedRule.IsRoot()
                    ? range.GetStartPos()
                    : prevDottedRule.GetWordsRange().GetEndPos() + 1;


    if (startPos == absEndPos) {


      const ChartCellLabel &sourceWordLabel = GetSourceAt(absEndPos);
      const Word &sourceWord = sourceWordLabel.GetLabel();
      const PhraseDictionaryNodeSCFG *node = prevDottedRule.GetLastNode().GetChild(sourceWord);


      if (node != NULL) {

#ifdef USE_BOOST_POOL
        DottedRuleInMemory *dottedRule = m_dottedRulePool.malloc();
        new (dottedRule) DottedRuleInMemory(*node, sourceWordLabel,
                                            prevDottedRule);
#else
        DottedRuleInMemory *dottedRule = new DottedRuleInMemory(*node,
                                                                sourceWordLabel,
                                                                prevDottedRule);
#endif
        dottedRuleCol.Add(relEndPos+1, dottedRule);
      }
    }


    size_t endPos, stackInd;


    if (startPos > absEndPos)
      continue;

    else if (startPos == range.GetStartPos() && range.GetEndPos() > range.GetStartPos()) {


      endPos = absEndPos - 1;
      stackInd = relEndPos;
    }
    else
    {
      endPos = absEndPos;
      stackInd = relEndPos + 1;
    }


    ExtendPartialRuleApplication(prevDottedRule, startPos, endPos, stackInd,
                                 dottedRuleCol);
  }


  DottedRuleList &rules = dottedRuleCol.Get(relEndPos + 1);


  DottedRuleList::const_iterator iterRule;
  for (iterRule = rules.begin(); iterRule != rules.end(); ++iterRule) {
    const DottedRuleInMemory &dottedRule = **iterRule;
    const PhraseDictionaryNodeSCFG &node = dottedRule.GetLastNode();


    const TargetPhraseCollection *tpc = node.GetTargetPhraseCollection();


    if (tpc != NULL) {
      AddCompletedRule(dottedRule, *tpc, range, outColl);
    }
  }

  dottedRuleCol.Clear(relEndPos+1);
}
