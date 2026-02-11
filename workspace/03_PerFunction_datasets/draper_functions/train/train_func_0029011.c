gradient(const ClpSimplex * model,
                                 const double * solution,
                                 double * gradient,
                                 double & functionValue,
                                 double & offset,
                                 bool useScaling,
                                 bool refresh) const
{
     if (refresh || !lastGradient_) {
          offset_ = 0.0;
          functionValue_ = 0.0;
          if (!lastGradient_)
               lastGradient_ = new double[numberColumns_];
          CoinZeroN(lastGradient_, numberColumns_);
          bool scaling = (model && model->rowScale() && useScaling);
          if (!scaling) {
               int iColumn;
               for (iColumn = 0; iColumn < numberQuadraticColumns_; iColumn++) {
                    double valueI = solution[iColumn];
                    CoinBigIndex j;
                    for (j = start_[iColumn]; j < start_[iColumn+1]; j++) {
                         int jColumn = column_[j];
                         if (jColumn >= 0) {
                              double valueJ = solution[jColumn];
                              double elementValue = coefficient_[j];
                              if (iColumn != jColumn) {
                                   offset_ -= valueI * valueJ * elementValue;
                                   double gradientI = valueJ * elementValue;
                                   double gradientJ = valueI * elementValue;
                                   lastGradient_[iColumn] += gradientI;
                                   lastGradient_[jColumn] += gradientJ;
                              } else {
                                   offset_ -= 0.5 * valueI * valueI * elementValue;
                                   double gradientI = valueI * elementValue;
                                   lastGradient_[iColumn] += gradientI;
                              }
                         } else {

                              lastGradient_[iColumn] += coefficient_[j];
                              functionValue_ += valueI * coefficient_[j];
                         }
                    }
               }
               functionValue_ -= offset_;
          } else {
               abort();

               const double * columnScale = model->columnScale();
               for (int i = 0; i < numberCoefficients_; i++) {
                    int iColumn = column_[i];
                    double value = solution[iColumn];
                    double coefficient = coefficient_[i] * columnScale[iColumn];
                    functionValue_ += value * coefficient;
                    lastGradient_[iColumn] = coefficient;
               }
          }
     }
     functionValue = functionValue_;
     offset = offset_;
     CoinMemcpyN(lastGradient_, numberColumns_, gradient);
     return 0;
}
