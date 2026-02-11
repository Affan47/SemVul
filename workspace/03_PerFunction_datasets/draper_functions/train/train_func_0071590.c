copy(const GAGeneticAlgorithm & g){
  GAGeneticAlgorithm::copy(g);
  const GASteadyStateGA& ga = DYN_CAST(const GASteadyStateGA&, g);

  pRepl = ga.pRepl;
  nRepl = ga.nRepl;

  if(tmpPop) tmpPop->copy(*(ga.tmpPop));
  else tmpPop = ga.tmpPop->clone();
  tmpPop->geneticAlgorithm(*this);

  which = ga.which;
}
