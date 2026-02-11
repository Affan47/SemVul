getThetaPeaks(int* sumpeak1, int* sumpeak2){
  unsigned short curMax1, curMax2;
  unsigned short curVal1, curVal2;

  for (int i=0; i<THETA_BOUND; i++){
    curMax1 = 0;
    curMax2 = 0;

    for (int j=0; j<RADIUS_SIZE; j++){
      curVal1 = this->peak1map[i*RADIUS_SIZE + j];
      curVal2 = this->peak2map[i*RADIUS_SIZE + j];
      if (curVal1 > curMax1) curMax1 = curVal1;
      if (curVal2 > curMax2) curMax2 = curVal2;
    }

    sumpeak1[i] = (int)curMax1;
    sumpeak2[i] = (int)curMax2;
  }

  return this->Num_Points;
}
