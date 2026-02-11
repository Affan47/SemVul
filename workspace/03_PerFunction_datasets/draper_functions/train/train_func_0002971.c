ann2ivarsel(AST::Node* ann, Rnd rnd, double decay) {
    if (AST::Atom* s = dynamic_cast<AST::Atom*>(ann)) {
      if (s->id == "input_order")
        return TieBreak<IntVarBranch>(INT_VAR_NONE());
      if (s->id == "first_fail")
        return TieBreak<IntVarBranch>(INT_VAR_SIZE_MIN());
      if (s->id == "anti_first_fail")
        return TieBreak<IntVarBranch>(INT_VAR_SIZE_MAX());
      if (s->id == "smallest")
        return TieBreak<IntVarBranch>(INT_VAR_MIN_MIN());
      if (s->id == "largest")
        return TieBreak<IntVarBranch>(INT_VAR_MAX_MAX());
      if (s->id == "occurrence")
        return TieBreak<IntVarBranch>(INT_VAR_DEGREE_MAX());
      if (s->id == "max_regret")
        return TieBreak<IntVarBranch>(INT_VAR_REGRET_MIN_MAX());
      if (s->id == "most_constrained")
        return TieBreak<IntVarBranch>(INT_VAR_SIZE_MIN(),
                                      INT_VAR_DEGREE_MAX());
      if (s->id == "random") {
        return TieBreak<IntVarBranch>(INT_VAR_RND(rnd));
      }
      if (s->id == "afc_min")
        return TieBreak<IntVarBranch>(INT_VAR_AFC_MIN(decay));
      if (s->id == "afc_max")
        return TieBreak<IntVarBranch>(INT_VAR_AFC_MAX(decay));
      if (s->id == "afc_size_min")
        return TieBreak<IntVarBranch>(INT_VAR_AFC_SIZE_MIN(decay));
      if (s->id == "afc_size_max") {
        return TieBreak<IntVarBranch>(INT_VAR_AFC_SIZE_MAX(decay));
      }
      if (s->id == "activity_min")
        return TieBreak<IntVarBranch>(INT_VAR_ACTIVITY_MIN(decay));
      if (s->id == "activity_max")
        return TieBreak<IntVarBranch>(INT_VAR_ACTIVITY_MAX(decay));
      if (s->id == "activity_size_min")
        return TieBreak<IntVarBranch>(INT_VAR_ACTIVITY_SIZE_MIN(decay));
      if (s->id == "activity_size_max")
        return TieBreak<IntVarBranch>(INT_VAR_ACTIVITY_SIZE_MAX(decay));
    }
    std::cerr << "Warning, ignored search annotation: ";
    ann->print(std::cerr);
    std::cerr << std::endl;
    return TieBreak<IntVarBranch>(INT_VAR_NONE());
  }
