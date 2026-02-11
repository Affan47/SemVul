applyRowCuts(int numberCuts, const OsiRowCut * cuts)
{
  if (numberCuts) {

    lastAlgorithm_=999;


    const OsiRowCut * * cutsp = new const OsiRowCut * [numberCuts];
    for (int i=0;i<numberCuts;i++)
      cutsp[i] = &cuts[i];

    applyRowCuts(numberCuts, cutsp);

    delete [] cutsp;
  }
}
