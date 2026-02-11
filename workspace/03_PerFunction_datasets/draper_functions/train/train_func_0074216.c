computeKnownBitsForMinMax(const SDValue Op0,
                                      const SDValue Op1,
                                      APInt &KnownZero,
                                      APInt &KnownOne,
                                      const SelectionDAG &DAG,
                                      unsigned Depth) {
  APInt Op0Zero, Op0One;
  APInt Op1Zero, Op1One;
  DAG.computeKnownBits(Op0, Op0Zero, Op0One, Depth);
  DAG.computeKnownBits(Op1, Op1Zero, Op1One, Depth);

  KnownZero = Op0Zero & Op1Zero;
  KnownOne = Op0One & Op1One;
}
