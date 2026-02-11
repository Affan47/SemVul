columnStatusString (int j) const

{ Status statj = getColumnStatus(j) ;

  switch (statj)
  { case isFree: { return ("NBFR") ; }
    case basic: { return ("B") ; }
    case atUpperBound: { return ("NBUB") ; }
    case atLowerBound: { return ("NBLB") ; }
    case superBasic: { return ("SB") ; }
    default: { return ("INVALID!") ; }
  }
}
