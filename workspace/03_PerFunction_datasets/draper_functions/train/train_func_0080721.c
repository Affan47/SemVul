EvaluateSymbolicAdd(const MCValue &LHS,const MCSymbolRefExpr *RHS_A,
                                const MCSymbolRefExpr *RHS_B, int64_t RHS_Cst,
                                MCValue &Res) {

  if ((LHS.getSymA() && RHS_A) ||
      (LHS.getSymB() && RHS_B))
    return false;

  const MCSymbolRefExpr *A = LHS.getSymA() ? LHS.getSymA() : RHS_A;
  const MCSymbolRefExpr *B = LHS.getSymB() ? LHS.getSymB() : RHS_B;
  if (B) {


    if (!A)
      return false;
  }
  Res = MCValue::get(A, B, LHS.getConstant() + RHS_Cst);
  return true;
}
