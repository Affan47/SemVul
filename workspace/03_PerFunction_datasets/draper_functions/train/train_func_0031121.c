TypesAreContradictory(MVT::SimpleValueType T1,
                                  MVT::SimpleValueType T2) {


  if (T1 == T2) return false;


  if (T1 == MVT::iPTR)
    return !MVT(T2).isInteger() || MVT(T2).isVector();

  if (T2 == MVT::iPTR)
    return !MVT(T1).isInteger() || MVT(T1).isVector();


  return true;
}
