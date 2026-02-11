findClosestMatchingDominator(const SCEV *CandidateExpr,
                                              Instruction *Dominatee) {
  auto Pos = SeenExprs.find(CandidateExpr);
  if (Pos == SeenExprs.end())
    return nullptr;

  auto &Candidates = Pos->second;


  while (!Candidates.empty()) {


    if (Value *Candidate = Candidates.back()) {
      Instruction *CandidateInstruction = cast<Instruction>(Candidate);
      if (DT->dominates(CandidateInstruction, Dominatee))
        return CandidateInstruction;
    }
    Candidates.pop_back();
  }
  return nullptr;
}
