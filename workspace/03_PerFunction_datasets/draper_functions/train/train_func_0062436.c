FillRowCol_(Index n_entries, const ExpandedMultiVectorMatrix& matrix, Index row_offset, Index col_offset, Index* iRow, Index* jCol)
  {
    row_offset++;
    col_offset++;
    const Index nRows = matrix.NRows();
    SmartPtr<const ExpansionMatrix> P = matrix.GetExpansionMatrix();
    if (IsValid(P)) {
      const Index* exppos = P->ExpandedPosIndices();
      const Index nExp = P->NCols();
      DBG_ASSERT(n_entries = nRows*nExp);
      for (Index irow = row_offset; irow < row_offset+nRows; irow++) {
        for (Index j=0; j<nExp; j++) {
          *(iRow++) = irow;
          *(jCol++) = col_offset + exppos[j];
        }
      }
    }
    else {
      const Index nCols =  matrix.NCols();
      DBG_ASSERT(n_entries = nRows*nCols);
      for (Index irow = row_offset; irow < row_offset+nRows; irow++) {
        for (Index jcol = col_offset; jcol < col_offset+nCols; jcol++) {
          *(iRow++) = irow;
          *(jCol++) = jcol;
        }
      }
    }
  }
