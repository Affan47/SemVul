extract_ngrams(const vector<Word >& sentence, map < Phrase, int >  & allngrams)
{
  for (int k = 0; k < (int)bleu_order; k++) {
    for(int i =0; i < max((int)sentence.size()-k,0); i++) {
      Phrase ngram( k+1);
      for ( int j = i; j<= i+k; j++) {
        ngram.AddWord(sentence[j]);
      }
      ++allngrams[ngram];
    }
  }
}
