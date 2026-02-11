branch(Home home, const IntVarArgs& x,
         IntVarBranch vars, IntValBranch vals,
         const Symmetries& syms,
         IntBranchFilter bf, IntVarValPrint vvp) {
    using namespace Int;
    if (home.failed()) return BrancherHandle();
    vars.expand(home,x);
    ViewArray<IntView> xv(home,x);
    ViewSel<IntView>* vs[1] = {
      Branch::viewselint(home,vars)
    };
    switch (vals.select()) {
    case IntValBranch::SEL_SPLIT_MIN:
    case IntValBranch::SEL_SPLIT_MAX:
    case IntValBranch::SEL_RANGE_MIN:
    case IntValBranch::SEL_RANGE_MAX:
    case IntValBranch::SEL_VALUES_MIN:
    case IntValBranch::SEL_VALUES_MAX:
      throw LDSBBadValueSelection("Int::LDSB::branch");
      break;
    case IntValBranch::SEL_VAL_COMMIT:
      if (vals.commit() != NULL)
        throw LDSBBadValueSelection("Int::LDSB::branch");


    default:


      VariableMap variableMap;
      for (int i = 0 ; i < x.size() ; i++)
        variableMap[x[i].varimp()] = i;


      int n = syms.size();
      SymmetryImp<IntView>** array =
        static_cast<Space&>(home).alloc<SymmetryImp<IntView>* >(n);
      for (int i = 0 ; i < n ; i++) {
        array[i] = createIntSym(home, syms[i], variableMap);
      }

      return LDSBBrancher<IntView,1,int,2>::post
        (home,xv,vs,Branch::valselcommitint(home,x.size(),vals),
         array,n,bf,vvp);
    }
  }
