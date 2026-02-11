scores(STD_OSTREAM & os, int w){
  if(w == NoScores) w = which;

  for(unsigned int i=0; i<nscrs; i++){
    os << gen[i];
    if(w & Mean) os << "\t" << aveScore[i];
    if(w & Maximum)  os << "\t" << maxScore[i];
    if(w & Minimum)  os << "\t" << minScore[i];
    if(w & Deviation)  os << "\t" << devScore[i];
    if(w & Diversity)  os << "\t" << divScore[i];
    os << "\n";
  }
  return 0;
}
