gutsOfCopyOf(const bool colordered,
			      const int minor, const int major,
			      const CoinBigIndex numels,
			      const double * elem, const int * ind,
			      const CoinBigIndex * start, const int * len,
			      const double extraMajor, const double extraGap)
{
   colOrdered_ = colordered;
   majorDim_ = major;
   minorDim_ = minor;
   size_ = numels;

   extraGap_ = extraGap;
   extraMajor_ = extraMajor;

   maxMajorDim_ = CoinLengthWithExtra(majorDim_, extraMajor_);

   if (maxMajorDim_ > 0) {
     delete [] length_;
     length_ = new int[maxMajorDim_];
     if (len == 0) {
       std::adjacent_difference(start + 1, start + (major + 1), length_);
       length_[0] -= start[0];
     } else {
       CoinMemcpyN(len, major, length_);
     }
     delete [] start_;
     start_ = new CoinBigIndex[maxMajorDim_+1];
     start_[0]=0;
     CoinMemcpyN(start, major+1, start_);
   } else {

     delete [] length_;
     length_ = NULL;
     delete [] start_;
     start_ = new CoinBigIndex[1];
     start_[0]=0;
   }

   maxSize_ = maxMajorDim_ > 0 ? start_[major] : 0;
   maxSize_ = CoinLengthWithExtra(maxSize_, extraMajor_);

   if (maxSize_ > 0) {
     delete [] element_;
     delete []index_;
     element_ = new double[maxSize_];
     index_ = new int[maxSize_];


     for (int i = majorDim_ - 1; i >= 0; --i) {
       CoinMemcpyN(ind + start[i], length_[i], index_ + start_[i]);
       CoinMemcpyN(elem + start[i], length_[i], element_ + start_[i]);
     }
   }
}
