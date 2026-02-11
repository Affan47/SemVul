OutputFeatureValuesForSLF(const Hypothesis* hypo, bool zeros, std::ostream &outputSearchGraphStream) const
{
  outputSearchGraphStream.setf(std::ios::fixed);
  outputSearchGraphStream.precision(6);


  const StaticData& staticData = StaticData::Instance();
  const TranslationSystem& system = staticData.GetTranslationSystem(TranslationSystem::DEFAULT);
  const vector<const StatelessFeatureFunction*>& slf =system.GetStatelessFeatureFunctions();
  const vector<const StatefulFeatureFunction*>& sff = system.GetStatefulFeatureFunctions();
  size_t featureIndex = 1;
  for (size_t i = 0; i < sff.size(); ++i) {
    featureIndex = OutputFeatureValuesForSLF(featureIndex, zeros, hypo, sff[i], outputSearchGraphStream);
  }
  for (size_t i = 0; i < slf.size(); ++i) {
    if (slf[i]->GetScoreProducerWeightShortName() != "u" &&
          slf[i]->GetScoreProducerWeightShortName() != "tm" &&
          slf[i]->GetScoreProducerWeightShortName() != "I" &&
          slf[i]->GetScoreProducerWeightShortName() != "g")
    {
      featureIndex = OutputFeatureValuesForSLF(featureIndex, zeros, hypo, slf[i], outputSearchGraphStream);
    }
  }
  const vector<PhraseDictionaryFeature*>& pds = system.GetPhraseDictionaries();
  for( size_t i=0; i<pds.size(); i++ ) {
    featureIndex = OutputFeatureValuesForSLF(featureIndex, zeros, hypo, pds[i], outputSearchGraphStream);
  }
  const vector<GenerationDictionary*>& gds = system.GetGenerationDictionaries();
  for( size_t i=0; i<gds.size(); i++ ) {
    featureIndex = OutputFeatureValuesForSLF(featureIndex, zeros, hypo, gds[i], outputSearchGraphStream);
  }

}
