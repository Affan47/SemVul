computeTemporaryTerms(map<expr_t, int> &reference_count,
                                     temporary_terms_t &temporary_terms,
                                     map<expr_t, pair<int, int> > &first_occurence,
                                     int Curr_block,
                                     vector<vector<temporary_terms_t> > &v_temporary_terms,
                                     int equation) const
{
  expr_t this2 = const_cast<TrinaryOpNode *>(this);
  map<expr_t, int>::iterator it = reference_count.find(this2);
  if (it == reference_count.end())
    {
      reference_count[this2] = 1;
      first_occurence[this2] = make_pair(Curr_block, equation);
      arg1->computeTemporaryTerms(reference_count, temporary_terms, first_occurence, Curr_block, v_temporary_terms, equation);
      arg2->computeTemporaryTerms(reference_count, temporary_terms, first_occurence, Curr_block, v_temporary_terms, equation);
      arg3->computeTemporaryTerms(reference_count, temporary_terms, first_occurence, Curr_block, v_temporary_terms, equation);
    }
  else
    {
      reference_count[this2]++;
      if (reference_count[this2] * cost(temporary_terms, false) > MIN_COST_C)
        {
          temporary_terms.insert(this2);
          v_temporary_terms[first_occurence[this2].first][first_occurence[this2].second].insert(this2);
        }
    }
}
