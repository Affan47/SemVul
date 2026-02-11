print() const
{
  int i ;
  int numberBasic=0;
  for (i=0;i<numStructural_;i++) {
    Status status = getStructStatus(i);
    if (status==CoinWarmStartBasis::basic)
      numberBasic++;
  }
  int numberStructBasic = numberBasic;
  for (i=0;i<numArtificial_;i++) {
    Status status = getArtifStatus(i);
    if (status==CoinWarmStartBasis::basic)
      numberBasic++;
  }
  std::cout<<"Basis "<<this<<" has "<<numArtificial_<<" rows and "
	   <<numStructural_<<" columns, "
	   <<numberBasic<<" basic, of which "<<numberStructBasic
	   <<" were columns"<<std::endl;
  std::cout<<"Rows:"<<std::endl;
  char type[]={'F','B','U','L'};

  for (i=0;i<numArtificial_;i++)
    std::cout<<type[getArtifStatus(i)];
  std::cout<<std::endl;
  std::cout<<"Columns:"<<std::endl;

  for (i=0;i<numStructural_;i++)
    std::cout<<type[getStructStatus(i)];
  std::cout<<std::endl;
}
