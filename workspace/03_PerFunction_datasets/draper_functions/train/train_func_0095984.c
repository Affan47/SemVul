isBasisFor(const Candidate &Basis,
                                            const Candidate &C) {
  return (Basis.Ins != C.Ins &&


          Basis.Ins->getType() == C.Ins->getType() &&

          DT->dominates(Basis.Ins->getParent(), C.Ins->getParent()) &&

          Basis.Base == C.Base && Basis.Stride == C.Stride &&
          Basis.CandidateKind == C.CandidateKind);
}
