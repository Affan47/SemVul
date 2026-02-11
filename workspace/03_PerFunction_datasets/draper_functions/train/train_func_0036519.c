getStat(int e, int f){
  int f_index = e*numBuckets + f/bucketSize;

  if (e>=V_e){ return 0.0; }
  if (t[f_index]==0){ return 0.0; }

  return t[f_index]->getScore(f);
}
