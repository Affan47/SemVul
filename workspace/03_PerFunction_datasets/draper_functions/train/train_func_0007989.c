initTransitions(Bitext* b, double** transition){
  int sourceLen = b->getSourceLength();
  int targetLen = b->getTargetLength();

  if (normalized){
    double normalization = 0.0;
    for (int ii=1; ii <=sourceLen; ii++){
      int iiDepth = b->getDepthOfSrcWordAt(ii);


      transition[0][ii] = initCount[ii];
      normalization += transition[0][ii];
    }
    if (normalization > 0.0){
      for (int ii=1; ii<=sourceLen; ii++){
	transition[0][ii] /= normalization;
      }
    }

    transition[0][sourceLen+1] = 0.0;

    for (int i=1; i<=sourceLen; i++){

      normalization = 0.0;
      for (int ii=1; ii<=sourceLen; ii++){
	int ancestor = b->getCommonAncestorOfSrcWordsAt(i, ii);
	int iDepth = b->getDepthOfSrcWordAt(i) - b->getDepthOfSrcWordAt(ancestor);
	int iiDepth = b->getDepthOfSrcWordAt(ii) - b->getDepthOfSrcWordAt(ancestor);
	int direction = (i>ii)?0:1;

	int c = useWordFeatures ? b->getSourceFeatureAt(i, partitionFeature) : 0;

	transition[i][ii] = depthDistortionCount[c][direction][iDepth][iiDepth];
	normalization += transition[i][ii];

      }

      if (true){
	int iDepth = b->getDepthOfSrcWordAt(i);
	transition[i][sourceLen+1] = termCount[sourceLen-i];

      } else {
	transition[i][sourceLen+1] = 1.0/(sourceLen+1);
      }

      if (normalization > 0.0){
	for (int ii=1; ii<=sourceLen; ii++){
	  transition[i][ii] /= normalization;
	}
      }
    }

  } else {
    if (nonUniformInit){
      skewedTransition(b, transition, initExponent);
    } else {
      uniformTransition(b, transition);
    }
  }
}
