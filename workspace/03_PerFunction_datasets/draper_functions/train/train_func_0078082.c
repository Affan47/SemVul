getRadBeforeFlav(const int RadAfter, const int EmtAfter,
      const Event& event) {

  int type = event[RadAfter].isFinal() ? 1 :-1;
  int emtID  = event[EmtAfter].id();
  int radID  = event[RadAfter].id();
  int emtCOL = event[EmtAfter].col();
  int radCOL = event[RadAfter].col();
  int emtACL = event[EmtAfter].acol();
  int radACL = event[RadAfter].acol();

  bool colConnected = ((type == 1) && ( (emtCOL !=0 && (emtCOL ==radACL))
                                     || (emtACL !=0 && (emtACL ==radCOL)) ))
                    ||((type ==-1) && ( (emtCOL !=0 && (emtCOL ==radCOL))
                                     || (emtACL !=0 && (emtACL ==radACL)) ));


  if ( emtID == 21 )
    return radID;

  if ( type == 1 && emtID == -radID && !colConnected )
    return 21;

  if ( type ==-1 && radID == 21 )
    return -emtID;

  if ( type ==-1 && emtID != 21 && radID != 21 && !colConnected )
    return 21;


  double m2final = (event[RadAfter].p()+ event[EmtAfter].p()).m2Calc();

  if ( emtID == 22 || emtID == 23 ) return radID;

  if ( type == 1 && emtID == -radID && colConnected && sqrt(m2final) <= 10. )
    return 22;

  if ( type == 1 && emtID == -radID && colConnected && sqrt(m2final)  > 10. )
    return 23;

  if ( type ==-1 && (radID == 22 || radID == 23) )
    return -emtID;

  if ( type ==-1 && abs(emtID) < 10 && abs(radID) < 10 && colConnected )
    return 22;


  if ( emtID == 24 && radID < 0 ) return radID + 1;
  if ( emtID == 24 && radID > 0 ) return radID + 1;


  if ( emtID ==-24 && radID < 0 ) return radID - 1;
  if ( emtID ==-24 && radID > 0 ) return radID - 1;


  return 0;

}
