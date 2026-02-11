checkCentroidUniqueness(double *adWeight, int *anCentroids, int nK)
{
  int i = 0, j = 0, l = 0;
  int anUnique[nK];
  double dMinWeight = MIN_WEIGHT;

  if(bLate == TRUE){dMinWeight = MIN_WEIGHT_LATE;}

  for(i = 0; i < nK; i++){
    anUnique[i] = TRUE;

    if(adWeight[i] < dMinWeight){
      anUnique[i] = NOT_SET;
    }
  }

  for(i = 0; i < nK; i++){

    if(anUnique[i] == TRUE){

      for(j = i + 1; j < nK; j++){

	if(anUnique[j] == TRUE){

	  if(anCentroids[i] == anCentroids[j]){
	    anUnique[j] = FALSE;
	    adWeight[i] += adWeight[j];
	    adWeight[j] = 0.0;
	  }
	}
      }
    }
  }

}
