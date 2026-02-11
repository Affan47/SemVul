validateCuts (const OsiCuts & cs,
				     int first, int last) const
{
  int nbad=0;
  int i;
  const double epsilon=1.0e-8;
  const int nRowCuts = CoinMin(cs.sizeRowCuts(),last);

  for (i=first; i<nRowCuts; i++){

    OsiRowCut rcut = cs.rowCut(i);
    CoinPackedVector rpv = rcut.row();
    const int n = rpv.getNumElements();
    const int * indices = rpv.getIndices();
    const double * elements = rpv.getElements();
    int k;
    double lb=rcut.lb();
    double ub=rcut.ub();

    double sum=0.0;

    for (k=0; k<n; k++){
      int column=indices[k];
      sum += knownSolution_[column]*elements[k];
    }

    if (sum >ub + epsilon ||sum < lb - epsilon) {
      double violation=CoinMax(sum-ub,lb-sum);
      std::cout<<"Cut "<<i<<" with "<<n
	  <<" coefficients, cuts off known solution by "<<violation
          <<", lo="<<lb<<", ub="<<ub<<std::endl;
      for (k=0; k<n; k++){
	int column=indices[k];
        std::cout<<"( "<<column<<" , "<<elements[k]<<" ) ";
	if ((k%4)==3)
	  std::cout <<std::endl;
      }
      std::cout <<std::endl;
      std::cout <<"Non zero solution values are"<<std::endl;
      int j=0;
      for (k=0; k<n; k++){
	int column=indices[k];
	if (fabs(knownSolution_[column])>1.0e-9) {
	  std::cout<<"( "<<column<<" , "<<knownSolution_[column]<<" ) ";
	  if ((j%4)==3)
	    std::cout <<std::endl;
	  j++;
	}
      }
      std::cout <<std::endl;
      nbad++;
    }
  }
  return nbad;
}
