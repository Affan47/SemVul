FillValues_(Index n_entries, const IdentityMatrix& matrix, Number* values)
  {
    DBG_ASSERT(n_entries == matrix.Dim());
    Number factor = matrix.GetFactor();
    for (Index i=0; i<n_entries; i++) {
      values[i] = factor;
    }
  }
