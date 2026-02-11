calculate_score(const vector< vector<const Factor*> > & sents, int ref, int hyp,  vector < map < vector < const Factor *>, int > > & ngram_stats )
{
  int comps_n = 2*BLEU_ORDER+1;
  vector<int> comps(comps_n);
  float logbleu = 0.0, brevity;

  int hyp_length = sents[hyp].size();

  for (int i =0; i<BLEU_ORDER; i++) {
    comps[2*i] = 0;
    comps[2*i+1] = max(hyp_length-i,0);
  }

  map< vector < const Factor * > ,int > & hyp_ngrams = ngram_stats[hyp] ;
  map< vector < const Factor * >, int > & ref_ngrams = ngram_stats[ref] ;

  for (map< vector< const Factor * >, int >::iterator it = hyp_ngrams.begin();
       it != hyp_ngrams.end(); it++) {
    map< vector< const Factor * >, int >::iterator ref_it = ref_ngrams.find(it->first);
    if(ref_it != ref_ngrams.end()) {
      comps[2* (it->first.size()-1)] += min(ref_it->second,it->second);
    }
  }
  comps[comps_n-1] = sents[ref].size();

  for (int i=0; i<BLEU_ORDER; i++) {
    if (comps[0] == 0)
      return 0.0;
    if ( i > 0 )
      logbleu += log((float)comps[2*i]+SMOOTH)-log((float)comps[2*i+1]+SMOOTH);
    else
      logbleu += log((float)comps[2*i])-log((float)comps[2*i+1]);
  }
  logbleu /= BLEU_ORDER;
  brevity = 1.0-(float)comps[comps_n-1]/comps[1];
  if (brevity < 0.0)
    logbleu += brevity;
  return exp(logbleu);
}
