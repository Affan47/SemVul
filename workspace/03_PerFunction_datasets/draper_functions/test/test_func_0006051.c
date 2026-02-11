CopyMatrix(unsigned int matrixIndex1, unsigned int matrixIndex2)
{
  ColumnArray  cols;
  unsigned int r;

  this->InitializeMatrix(matrixIndex2);
  for( r = 0; r < this->m_Order; r++ )
    {
    this->GetColumnsOfNonZeroMatrixElementsInRow(r, cols, matrixIndex1);
    for( LinearSystemWrapper::ColumnArray::iterator c = cols.begin(); c != cols.end(); ++c )
      {
      this->SetMatrixValue(r, *c, this->GetMatrixValue(r, *c, matrixIndex1), matrixIndex2);
      }
    }
}
