symbolic1(const CoinBigIndex * Astart, const int * Arow)
{
     int * marked = reinterpret_cast<int *> (workInteger_);
     int iRow;

     for (iRow = 0; iRow < numberRows_; iRow++) {
          marked[iRow] = -1;
          link_[iRow] = -1;
          choleskyStart_[iRow] = 0;
     }
     for (iRow = 0; iRow < numberRows_; iRow++) {
          marked[iRow] = iRow;
          for (CoinBigIndex j = Astart[iRow]; j < Astart[iRow+1]; j++) {
               int kRow = Arow[j];
               while (marked[kRow] != iRow ) {
                    if (link_[kRow] < 0 )
                         link_[kRow] = iRow;
                    choleskyStart_[kRow]++;
                    marked[kRow] = iRow;
                    kRow = link_[kRow];
               }
          }
     }
     sizeFactor_ = 0;
     for (iRow = 0; iRow < numberRows_; iRow++) {
          int number = choleskyStart_[iRow];
          choleskyStart_[iRow] = sizeFactor_;
          sizeFactor_ += number;
     }
     choleskyStart_[numberRows_] = sizeFactor_;
     return sizeFactor_;;
}
