dualRanging(int numberCheck, const int * which,
                            double * costIncrease, int * sequenceIncrease,
                            double * costDecrease, int * sequenceDecrease,
                            double * valueIncrease, double * valueDecrease)
{
     int savePerturbation = perturbation_;
     perturbation_ = 100;
      static_cast<ClpSimplexPrimal *> (this)->primal(0, 1);
     if (problemStatus_ == 10) {

          bool denseFactorization = initialDenseFactorization();

          setInitialDenseFactorization(true);

          int dummy;
          if ((matrix_->generalExpanded(this, 4, dummy) & 2) != 0) {

               double saveBound = dualBound_;
               if (upperOut_ > 0.0)
                    dualBound_ = 2.0 * upperOut_;
                static_cast<ClpSimplexDual *> (this)->dual(0, 1);
               dualBound_ = saveBound;
          } else {
	         static_cast<ClpSimplexPrimal *> (this)->primal(0, 1);
          }
          setInitialDenseFactorization(denseFactorization);
          if (problemStatus_ == 10)
               problemStatus_ = 0;
     }
     perturbation_ = savePerturbation;
     if (problemStatus_ || secondaryStatus_ == 6) {
          finish();
          return 1;
     }
     static_cast<ClpSimplexOther *> (this)->dualRanging(numberCheck, which,
               costIncrease, sequenceIncrease,
               costDecrease, sequenceDecrease,
               valueIncrease, valueDecrease);
     finish();
     return 0;
}
