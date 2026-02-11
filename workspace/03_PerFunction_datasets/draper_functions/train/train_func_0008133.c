UniformInitializer(GAGenome & c)
{
  GA3DBinaryStringGenome &child=DYN_CAST(GA3DBinaryStringGenome &, c);
  child.resize(GAGenome::ANY_SIZE,GAGenome::ANY_SIZE,GAGenome::ANY_SIZE);
  for(int i=child.width()-1; i>=0; i--)
    for(int j=child.height()-1; j>=0; j--)
      for(int k=child.depth()-1; k>=0; k--)
	child.gene(i,j,k, GARandomBit());
}
