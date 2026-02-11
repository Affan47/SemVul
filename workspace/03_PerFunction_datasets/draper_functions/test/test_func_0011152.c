initConstants() {


  vecM.clear(); vecG.clear(); vecP.clear(); vecA.clear(); vecW.clear();


  if (abs(pID[2]) == 221) {
    DECAYWEIGHTMAX = 10;
    pM[2] = particleDataPtr->m0(211); pM[3] = particleDataPtr->m0(311);
    vecM.push_back(0.8921); vecM.push_back(1.700);
    vecG.push_back(0.0513); vecG.push_back(0.235);
    vecP.push_back(0);      vecP.push_back(M_PI);
    vecA.push_back(1);      vecA.push_back(0.038);
  }


  else {
    if (abs(pID[2]) == 111)      DECAYWEIGHTMAX = 800;
    else if (abs(pID[2]) == 311) DECAYWEIGHTMAX = 6;
    pM[2] = particleDataPtr->m0(111); pM[3] = particleDataPtr->m0(211);
    vecM.push_back(0.7746); vecM.push_back(1.4080); vecM.push_back(1.700);
    vecG.push_back(0.1490); vecG.push_back(0.5020); vecG.push_back(0.235);
    vecP.push_back(0);      vecP.push_back(M_PI);   vecP.push_back(0);
    vecA.push_back(1.0);    vecA.push_back(0.167);  vecA.push_back(0.050);
  }
  calculateResonanceWeights(vecP, vecA, vecW);

}
