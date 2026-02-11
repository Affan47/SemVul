getTermFrequency()const{

  double lReturnValue(0);
  if(mPositiveRelevanceSum){
    lReturnValue += mPositiveTermFrequency/mPositiveRelevanceSum;
  }
  if(mNegativeRelevanceSum){


    lReturnValue -= 0.5 * fabs(mNegativeTermFrequency)/fabs(mNegativeRelevanceSum);
  }
  return lReturnValue;
}
