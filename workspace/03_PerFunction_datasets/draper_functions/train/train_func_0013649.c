addQueryFeature(double inRelevanceLevel,
					 const
					 CDocumentFrequencyElement&
					 inQueryFeature){

  if(inRelevanceLevel>0){
    mPositiveTermFrequency+=
      (inRelevanceLevel)*
      inQueryFeature.getDocumentFrequency();
  }else{
    mNegativeTermFrequency+=
      inRelevanceLevel*
      inQueryFeature.getDocumentFrequency();
  }
}
