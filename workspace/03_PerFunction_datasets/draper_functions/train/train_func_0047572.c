size(unsigned int popsize){
  if(popsize == n) return n;
  if(n == 0 && popsize > 0) {
    GAErr(GA_LOC, "GAPopuluation", "size", gaErrNoIndividuals);
    return n;
  }

  if(popsize > n){
    grow(popsize);
    for(unsigned int i=n; i<popsize; i++)
      rind[i] = rind[GARandomInt(0,n-1)]->clone(GAGenome::CONTENTS);
    rsorted = gaFalse;
  }
  else{
    for(unsigned int i=popsize; i<n; i++)
      delete rind[i];
  }

  memcpy(sind, rind, N * sizeof(GAGenome*));
  ssorted = scaled = statted = divved = selectready = gaFalse;
  n = popsize;

  if(evaluated == gaTrue) evaluate(gaTrue);

  return n;
}
