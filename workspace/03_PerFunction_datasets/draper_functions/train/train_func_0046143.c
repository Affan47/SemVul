dubiousWeights(const ClpSimplex * model, int * inputWeights) const
{
     int numberRows = model->numberRows();
     int numberColumns = matrix_->getNumCols();
     int number = numberRows + numberColumns;
     CoinBigIndex * weights = new CoinBigIndex[number];

     const int * row = matrix_->getIndices();
     const CoinBigIndex * columnStart = matrix_->getVectorStarts();
     const int * columnLength = matrix_->getVectorLengths();
     int i;
     for (i = 0; i < numberColumns; i++) {
          CoinBigIndex j;
          CoinBigIndex count = 0;
          for (j = columnStart[i]; j < columnStart[i] + columnLength[i]; j++) {
               int iRow = row[j];
               count += inputWeights[iRow];
          }
          weights[i] = count;
     }
     for (i = 0; i < numberRows; i++) {
          weights[i+numberColumns] = inputWeights[i];
     }
     return weights;
}
