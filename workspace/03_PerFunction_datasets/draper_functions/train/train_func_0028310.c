Read(std::istream& in,const std::vector<FactorType>& factorOrder)
{
  const StaticData &staticData = StaticData::Instance();

  string line;
  if (getline(in, line, '\n').eof())
    return 0;


  std::vector<XMLParseOutput> sourceLabels;
  std::vector<XmlOption*> xmlOptionsList;
  ProcessAndStripXMLTags(line, sourceLabels, xmlOptionsList);


  stringstream strme;
  strme << line << endl;

  Sentence::Read(strme, factorOrder);


  size_t sourceSize = GetSize();
  m_sourceChart.resize(sourceSize);

  for (size_t pos = 0; pos < sourceSize; ++pos) {
    m_sourceChart[pos].resize(sourceSize - pos);
  }


  vector<XMLParseOutput>::const_iterator iterLabel;
  for (iterLabel = sourceLabels.begin(); iterLabel != sourceLabels.end(); ++iterLabel) {
    const XMLParseOutput &labelItem = *iterLabel;
    const WordsRange &range = labelItem.m_range;
    const string &label = labelItem.m_label;
    AddChartLabel(range.GetStartPos() + 1, range.GetEndPos() + 1, label, factorOrder);
  }


  for (size_t startPos = 0; startPos < sourceSize; ++startPos) {
    for (size_t endPos = startPos; endPos < sourceSize; ++endPos) {
      AddChartLabel(startPos, endPos, staticData.GetInputDefaultNonTerminal(), factorOrder);
    }
  }


  if (staticData.GetXmlInputType() != XmlPassThrough ) {


    for(std::vector<XmlOption*>::const_iterator iterXmlOpts = xmlOptionsList.begin();
        iterXmlOpts != xmlOptionsList.end(); iterXmlOpts++) {

      const XmlOption *xmlOption = *iterXmlOpts;
      TargetPhrase *targetPhrase = new TargetPhrase(xmlOption->targetPhrase);
      *targetPhrase = xmlOption->targetPhrase;
      WordsRange *range = new WordsRange(xmlOption->range);
      const StackVec emptyStackVec;

      TargetPhraseCollection *tpc = new TargetPhraseCollection;
      tpc->Add(targetPhrase);

      ChartTranslationOptions *transOpt = new ChartTranslationOptions(*tpc, emptyStackVec, *range, 0.0f);
      m_xmlChartOptionsList.push_back(transOpt);


      delete xmlOption;
    }

  }

  return 1;
}
