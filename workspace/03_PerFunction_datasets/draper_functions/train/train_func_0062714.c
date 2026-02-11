operator=(const ClpLsqr & rhs)
{
     if (this != &rhs) {
          delete [] diag1_;
          diag1_ = ClpCopyOfArray(rhs.diag1_, nrows_);
          nrows_ = rhs.nrows_;
          ncols_ = rhs.ncols_;
          model_ = rhs.model_;
          diag2_ = rhs.diag2_;
     }
     return *this;
}
