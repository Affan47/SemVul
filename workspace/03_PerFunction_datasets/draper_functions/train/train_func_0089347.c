FillRowCol_(Index n_entries, const ExpansionMatrix& matrix, Index row_offset, Index col_offset, Index* iRow, Index* jCol)
  {
    DBG_ASSERT(n_entries == matrix.NCols());
    const Index* exp_pos = matrix.ExpandedPosIndices();
    row_offset++;
    col_offset++;
    for (Index i=0; i<n_entries; i++) {
      iRow[i] = exp_pos[i] + row_offset;
      jCol[i] = i + col_offset;
    }
  }
