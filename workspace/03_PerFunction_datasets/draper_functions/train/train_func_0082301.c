OutputFeatureScores( std::ostream& out, const TrellisPath &path, const FeatureFunction *ff, std::string &lastName )
{
  const StaticData &staticData = StaticData::Instance();
  bool labeledOutput = staticData.IsLabeledNBestList();


  if (ff->GetNumScoreComponents() != ScoreProducer::unlimited) {
    if( labeledOutput && lastName != ff->GetScoreProducerWeightShortName() ) {
      lastName = ff->GetScoreProducerWeightShortName();
      out << " " << lastName << ":";
    }
    vector<float> scores = path.GetScoreBreakdown().GetScoresForProducer( ff );
    for (size_t j = 0; j<scores.size(); ++j) {
      out << " " << scores[j];
    }
  }


  else {
    const FVector scores = path.GetScoreBreakdown().GetVectorForProducer( ff );


    if (! ff->GetSparseFeatureReporting()) {
      const FVector &weights = staticData.GetAllWeights().GetScoresVector();
      if (labeledOutput && !boost::contains(ff->GetScoreProducerDescription(), ":"))
        out << " " << ff->GetScoreProducerWeightShortName() << ":";
      out << " " << scores.inner_product(weights);
    }


    else {
      for(FVector::FNVmap::const_iterator i = scores.cbegin(); i != scores.cend(); i++)
	out << " " << i->first << ": " << i->second;


    }
  }
}
