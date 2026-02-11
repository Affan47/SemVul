join(const PseudoJet & j1,
	       const JetDefinition::Recombiner & recombiner){
  return join(vector<PseudoJet>(1,j1), recombiner);
}
