subsetTimes2(const ClpSimplex * model,
                            CoinIndexedVector * dj1,
                            const CoinIndexedVector * pi2, CoinIndexedVector * dj2,
                            double referenceIn, double devex,

                            unsigned int * reference,
                            double * weights, double scaleFactor)
{

     subsetTransposeTimes(model, pi2, dj1, dj2);
     bool killDjs = (scaleFactor == 0.0);
     if (!scaleFactor)
          scaleFactor = 1.0;


     int number = dj1->getNumElements();
     const int * index = dj1->getIndices();
     double * updateBy = dj1->denseVector();
     double * updateBy2 = dj2->denseVector();

     for (int j = 0; j < number; j++) {
          double thisWeight;
          double pivot;
          double pivotSquared;
          int iSequence = index[j];
          double value2 = updateBy[j];
          if (killDjs)
               updateBy[j] = 0.0;
          double modification = updateBy2[j];
          updateBy2[j] = 0.0;
          ClpSimplex::Status status = model->getStatus(iSequence);

          if (status != ClpSimplex::basic && status != ClpSimplex::isFixed) {
               thisWeight = weights[iSequence];
               pivot = value2 * scaleFactor;
               pivotSquared = pivot * pivot;

               thisWeight += pivotSquared * devex + pivot * modification;
               if (thisWeight < DEVEX_TRY_NORM) {
                    if (referenceIn < 0.0) {

                         thisWeight = CoinMax(DEVEX_TRY_NORM, DEVEX_ADD_ONE + pivotSquared);
                    } else {

                         thisWeight = referenceIn * pivotSquared;
                         if (reference(iSequence))
                              thisWeight += 1.0;
                         thisWeight = CoinMax(thisWeight, DEVEX_TRY_NORM);
                    }
               }
               weights[iSequence] = thisWeight;
          }
     }
     dj2->setNumElements(0);
}
