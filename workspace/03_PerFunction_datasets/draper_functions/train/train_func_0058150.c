setScore(const GAPopulation& pop){
  aveCur = pop.ave();
  maxCur = pop.max();
  minCur = pop.min();
  devCur = pop.dev();
  divCur = ((dodiv == gaTrue) ? pop.div() : (float)-1.0);

  if(Nscrs == 0) return;
  gen[nscrs] = curgen;
  aveScore[nscrs] = aveCur;
  maxScore[nscrs] = maxCur;
  minScore[nscrs] = minCur;
  devScore[nscrs] = devCur;
  divScore[nscrs] = divCur;
  nscrs++;
}
