postsolve (CoinPostsolveMatrix *prob) const
{
  const action *const &bndRecords = actions_ ;
  const int &numRecs = nactions_ ;

  double *&rlo = prob->rlo_ ;
  double *&rup = prob->rup_ ;
  unsigned char *&rowstat = prob->rowstat_ ;

# if PRESOLVE_CONSISTENCY > 0 || PRESOLVE_DEBUG > 0
# if PRESOLVE_DEBUG > 0
  std::cout
    << "Entering remove_dual_action::postsolve, " << numRecs
    << " bounds to restore." << std::endl ;
# endif
  presolve_check_threads(prob) ;
  presolve_check_sol(prob,2,2,2) ;
  presolve_check_nbasic(prob) ;
# endif


  for (int k = 0 ; k < numRecs ; k++) {
    const action &bndRec = bndRecords[k] ;
    const int &i = bndRec.ndx_ ;
    const double &rloi = bndRec.rlo_ ;
    const double &rupi = bndRec.rup_ ;

#   if PRESOLVE_DEBUG > 1
    std::cout << "NDUAL(eq): row(" << i << ")" ;
    if (rlo[i] != rloi) std::cout << " LB " << rlo[i] << " -> " << rloi ;
    if (rup[i] != rupi) std::cout << " UB " << rup[i] << " -> " << rupi ;
#   endif

    rlo[i] = rloi ;
    rup[i] = rupi ;
    if (rowstat) {
      unsigned char stati = prob->getRowStatus(i) ;
      if (stati == CoinPresolveMatrix::atUpperBound) {
        if (rloi <= -PRESOLVE_INF) {
	  rowstat[i] = CoinPresolveMatrix::atLowerBound ;
#         if PRESOLVE_DEBUG > 1
	  std::cout
	    << ", status forced to "
	    << statusName(static_cast<CoinPresolveMatrix::Status>(rowstat[i])) ;
#         endif
	}
      } else if (stati == CoinPresolveMatrix::atLowerBound) {
        if (rupi >= PRESOLVE_INF) {
	  rowstat[i] = CoinPresolveMatrix::atUpperBound ;
#         if PRESOLVE_DEBUG > 1
	  std::cout
	    << ", status forced to "
	    << statusName(static_cast<CoinPresolveMatrix::Status>(rowstat[i])) ;
#         endif
	}
      }
#     if PRESOLVE_DEBUG > 2
        else if (stati == CoinPresolveMatrix::basic) {
        std::cout << ", status is basic." ;
      } else if (stati == CoinPresolveMatrix::isFree) {
        std::cout << ", status is free?!" ;
      } else {
        unsigned int tmp = static_cast<unsigned int>(stati) ;
        std::cout << ", status is invalid (" << tmp << ")!" ;
      }
#     endif
    }
#   if PRESOLVE_DEBUG > 1
    std::cout << "." << std::endl ;
#   endif
  }

# if PRESOLVE_CONSISTENCY > 0 || PRESOLVE_DEBUG > 0
  presolve_check_threads(prob) ;
  presolve_check_sol(prob,2,2,2) ;
  presolve_check_nbasic(prob) ;
# if PRESOLVE_DEBUG > 0
  std::cout << "Leaving remove_dual_action::postsolve." << std::endl ;
# endif
# endif

  return ;
}
