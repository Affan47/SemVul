Load(const std::string &filePath, FactorDirection direction)
{
  FactorCollection &factorCollection = FactorCollection::Instance();

  const size_t numFeatureValuesInConfig = this->GetNumScoreComponents();


  InputFileStream inFile(filePath);
  if (!inFile.good()) {
    UserMessage::Add(string("Couldn't read ") + filePath);
    return false;
  }

  m_filePath = filePath;
  string line;
  size_t lineNum = 0;
  while(getline(inFile, line)) {
    ++lineNum;
    vector<string> token = Tokenize( line );


    Word *inputWord = new Word();
    Word outputWord;


    vector<string> factorString = Tokenize( token[0], "|" );
    for (size_t i = 0 ; i < GetInput().size() ; i++) {
      FactorType factorType = GetInput()[i];
      const Factor *factor = factorCollection.AddFactor( direction, factorType, factorString[i]);
      inputWord->SetFactor(factorType, factor);
    }

    factorString = Tokenize( token[1], "|" );
    for (size_t i = 0 ; i < GetOutput().size() ; i++) {
      FactorType factorType = GetOutput()[i];

      const Factor *factor = factorCollection.AddFactor( direction, factorType, factorString[i]);
      outputWord.SetFactor(factorType, factor);
    }

    size_t numFeaturesInFile = token.size() - 2;
    if (numFeaturesInFile < numFeatureValuesInConfig) {
      stringstream strme;
      strme << filePath << ":" << lineNum << ": expected " << numFeatureValuesInConfig
            << " feature values, but found " << numFeaturesInFile << std::endl;
      UserMessage::Add(strme.str());
      return false;
    }
    std::vector<float> scores(numFeatureValuesInConfig, 0.0f);
    for (size_t i = 0; i < numFeatureValuesInConfig; i++)
      scores[i] = FloorScore(TransformScore(Scan<float>(token[2+i])));

    Collection::iterator iterWord = m_collection.find(inputWord);
    if (iterWord == m_collection.end()) {
      m_collection[inputWord][outputWord].Assign(this, scores);
    } else {

      (iterWord->second)[outputWord].Assign(this, scores);
      delete inputWord;
    }
  }

  inFile.Close();
  return true;
}
