FillValues_(Index n_entries, const SumMatrix& matrix, Number* values)
  {
    Index total_n_entries = 0;
    for (Index i=0; i<matrix.NTerms(); i++) {

      Number retFactor = 0.0;
      SmartPtr<const Matrix> retTerm;
      matrix.GetTerm(i, retFactor, retTerm);
      Index term_n_entries = GetNumberEntries(*retTerm);
      total_n_entries += term_n_entries;
      FillValues(term_n_entries, *retTerm, values);


      IpBlasDscal(term_n_entries, retFactor, values, 1);


      values += term_n_entries;
    }
    DBG_ASSERT(total_n_entries == n_entries);
  }
